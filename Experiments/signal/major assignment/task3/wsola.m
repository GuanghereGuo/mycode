function main
    % --- 配置区域 ---
    filename = 'origin.wav'; 
    % filename = '../test1.wav';
    mode = 2;              % 1=变速不变调, 2=变调不变速
    speed_change = 2;    % 模式1参数: 0.5=慢速, 2.0=快速
    pitch_semitones = 4;   % 模式2参数: 4=升4个半音
    % enable_denoise = true;  % 开关降噪
    enable_denoise = false; % 关闭降噪
    % ----------------
    
    [x, fs] = audioread(filename);
    if size(x, 1) < size(x, 2), x = x'; end

    % === 新增：降噪处理 ===
    if enable_denoise
        disp('正在去除底噪...');
        x = denoise_process(x, fs);
        % [b, a] = butter(4, 100/(fs/2), 'high'); % 需要 Signal Processing Toolbox
        % x = filter(b, a, x);
    end
    % ====================
    
    if mode == 1
        % 变速不变调
        y = wsola_process(x, speed_change);
    elseif mode == 2
        % 变调不变速
        ratio = 2^(pitch_semitones / 12);
        alpha = 1 / ratio; 
        y_temp = wsola_process(x, alpha);
        
        % 重采样变调
        old_len = size(y_temp, 1);
        t_old = 0:old_len-1;
        t_new = 0 : ratio : old_len-1; 
        
        y = zeros(length(t_new), size(x, 2));
        for c = 1:size(x, 2)
            y(:, c) = interp1(t_old, y_temp(:, c), t_new, 'linear', 0);
        end
    else 
        % === 变调不变速 (男变女核心逻辑) ===
        
        % 1. 计算变调比率
        pitch_ratio = 2^(pitch_semitones / 12); % 例如 1.2599
        
        % 2. WSOLA 变调 (重采样 + 时间拉伸)
        % 这一步会把共振峰也拉伸 pitch_ratio 倍
        alpha = 1 / pitch_ratio; 
        y_temp = wsola_process(x, alpha);
        
        old_len = size(y_temp, 1);
        t_old = 0:old_len-1;
        t_new = 0 : pitch_ratio : old_len-1; 
        
        y_pitch_shifted = zeros(length(t_new), size(x, 2));
        for c = 1:size(x, 2)
            y_pitch_shifted(:, c) = interp1(t_old, y_temp(:, c), t_new, 'linear', 0);
        end
        
        % 3. 共振峰修正 (Formant Correction)
        % 策略：
        % 如果我们升调 (pitch_ratio > 1)，现在的共振峰也被拉高了 pitch_ratio。
        % 我们希望共振峰只拉高一点点 (比如 1.15 倍，而不是 1.26 倍)。
        % 所以我们需要把共振峰 "降" 回去一点。
        
        if pitch_ratio > 1 % 升调 (男 -> 女)
            % 典型的女性声道共振峰偏移约为 1.15 到 1.2
            target_formant_shift = 1.2; % 你可以调节这个参数优化听感 (1.10 - 1.20)
            
            % 修正系数 = 目标 / 当前 (当前已经被 WSOLA 拉到了 pitch_ratio)
            correction_ratio = target_formant_shift / pitch_ratio; 
            
        else % 降调 (女 -> 男)
            % 男性共振峰约为女性的 0.85
            target_formant_shift = 0.85;
            correction_ratio = target_formant_shift / pitch_ratio;
        end
        
        disp(['正在修正共振峰... 修正系数: ', num2str(correction_ratio)]);
        y = formant_process(y_pitch_shifted, fs, correction_ratio);
        
    end
    
    m = max(abs(y(:)));
    if m > 1, y = y ./ m; end
    
    sound(y, fs);
    audiowrite('processed_output.wav', y, fs);
end

function y = wsola_process(x, alpha)
    [N, nCh] = size(x);
    winLen = 1024;
    synHop = winLen / 2;
    anaHop = round(synHop * alpha);
    searchWin = 256;
    
    % 预分配空间
    y = zeros(ceil(N / alpha) + winLen * 2, nCh);
    win = hanning(winLen, 'periodic');
    
    synPos = 1;
    anaPos = 1;
    lastInputPos = 1;
    
    % 主循环：增加边界安全检查
    while true
        naturalPos = lastInputPos + synHop;
        
        % 1. 严格检查参考块是否越界，越界则停止
        if naturalPos + winLen - 1 > N
            break;
        end
        
        % 2. 检查分析指针是否处理完毕
        if anaPos + winLen + searchWin > N
            % 尝试最后一次匹配，如果空间不够则缩小搜索范围
            searchWin = max(0, N - winLen - anaPos);
            if searchWin < 10, break; end 
        end

        searchStart = max(1, anaPos - searchWin);
        searchEnd = min(N - winLen, anaPos + searchWin);
        
        % 提取单声道混合信号用于计算相关性
        if nCh > 1
            refBlock = sum(x(naturalPos : naturalPos + winLen - 1, :), 2);
            searchArea = sum(x(searchStart : searchEnd + winLen - 1, :), 2);
        else
            refBlock = x(naturalPos : naturalPos + winLen - 1);
            searchArea = x(searchStart : searchEnd + winLen - 1);
        end
        
        % FFT 互相关
        L = length(searchArea);
        M = length(refBlock);
        nFFT = 2^nextpow2(L + M);
        X = fft(searchArea, nFFT);
        Y = fft(flipud(refBlock), nFFT);
        c = ifft(X .* Y);
        c = real(c(M:L)); % 取有效部分
        
        [~, lag] = max(c);
        bestInputPos = searchStart + (lag - 1);
        
        % 叠加输出
        for cIdx = 1:nCh
            frame = x(bestInputPos : bestInputPos + winLen - 1, cIdx);
            y(synPos : synPos + winLen - 1, cIdx) = ...
                y(synPos : synPos + winLen - 1, cIdx) + frame .* win;
        end
        
        lastInputPos = bestInputPos;
        synPos = synPos + synHop;
        anaPos = anaPos + anaHop;
    end
    
    % 裁剪输出并处理可能的最后一段静音
    validLen = synPos + winLen / 2;
    if validLen > size(y, 1), validLen = size(y, 1); end
    y = y(1:validLen, :);
end

function y = denoise_process(x, fs)
% 简易谱减法降噪
% 假设：文件开头 0.25秒 为纯噪声样本

    [N, nCh] = size(x);
    y = zeros(N, nCh);
    
    % 参数设置
    winLen = 1024;
    hop = winLen / 2;
    win = hanning(winLen, 'periodic');
    
    % 1. 提取噪声样本 (前0.25秒)
    noise_dur = round(0.25 * fs);
    if noise_dur > N, noise_dur = N; end
    noise_segment = x(1:noise_dur, :);
    
    for c = 1:nCh
        % 2. 计算噪声的平均幅度谱
        % 使用简单的平均法估算噪声底
        n_spec_sum = zeros(winLen, 1);
        count = 0;
        pos = 1;
        while pos + winLen < noise_dur
            frame = noise_segment(pos:pos+winLen-1, c) .* win;
            n_spec_sum = n_spec_sum + abs(fft(frame));
            pos = pos + hop;
            count = count + 1;
        end
        if count > 0
            noise_profile = n_spec_sum / count;
        else
            noise_profile = abs(fft(noise_segment(1:min(winLen, end), c) .* win)); 
        end
        
        % 3. 对全信号进行处理 (STFT -> 减法 -> ISTFT)
        processed_ch = zeros(N + winLen, 1);
        pos = 1;
        write_pos = 1;
        
        % 谱减参数 (调节这两个值改变降噪力度)
        alpha = 2.0;    % 减法系数：越大去噪越狠，但容易产生水底音
        beta = 0.01;    % 频谱下限：防止频谱出现负值或过小的坑
        
        while pos + winLen < N
            frame = x(pos:pos+winLen-1, c);
            frame_win = frame .* win;
            
            spec = fft(frame_win);
            mag = abs(spec);
            phase = angle(spec);
            
            % --- 核心：谱减 ---
            % 幅度 = 原幅度 - alpha * 噪声幅度
            new_mag = mag - alpha * noise_profile;
            
            % 保证幅度不小于原幅度的 beta 倍 (避免音乐噪声)
            new_mag = max(new_mag, beta * mag); 
            
            % 重建复数谱
            new_spec = new_mag .* exp(1j * phase);
            
            % ISTFT & Overlap-Add
            frame_out = real(ifft(new_spec));
            processed_ch(write_pos : write_pos + winLen - 1) = ...
                processed_ch(write_pos : write_pos + winLen - 1) + frame_out;
            
            pos = pos + hop;
            write_pos = write_pos + hop;
        end
        
        y(:, c) = processed_ch(1:N);
    end
    
    % 归一化补偿窗函数增益 (简单处理)
    y = y * (hop/winLen) * 4; 
end

function y = formant_process(x, fs, shift_ratio)
% 共振峰移动滤波器
% x: 输入信号 (已经经过变调处理的信号)
% shift_ratio: 共振峰移动系数 
%   > 1.0 : 共振峰向高频移动 (变年轻/女性化，如果是男变女，通常配合变调使用)
%   < 1.0 : 共振峰向低频移动 (变深沉/男性化)
% 
% 核心原理：Source-Filter 模型解耦
% 1. 提取频谱包络 (Filter)
% 2. 将包络在频率轴上缩放
% 3. 将新包络应用回白化后的频谱 (Source)

    [N, nCh] = size(x);
    winLen = 1024;
    hop = winLen / 4; % 75% 重叠以保证平滑
    win = hanning(winLen, 'periodic');
    
    y = zeros(N, nCh);
    norm_win = zeros(N, 1);
    
    % 倒谱法参数
    nFFT = 2048;
    cep_cutoff = 40; % 倒谱截断点，用于分离包络 (Source-Filter分离)
    
    for c = 1:nCh
        pos = 1;
        while pos + winLen < N
            % 1. STFT
            frame = x(pos : pos + winLen - 1, c) .* win;
            spec = fft(frame, nFFT);
            mag = abs(spec);
            phase = angle(spec);
            
            % 2. 提取包络 (使用实倒谱 Real Cepstrum)
            log_mag = log(mag + eps);
            cepstrum = real(ifft(log_mag));
            
            % 低通滤波倒谱 (保留低倒频率成分，即包络)
            cep_env = zeros(size(cepstrum));
            cep_env(1:cep_cutoff) = cepstrum(1:cep_cutoff);
            cep_env(end-cep_cutoff+2:end) = cepstrum(end-cep_cutoff+2:end);
            
            % 恢复为频谱包络 (Envelope)
            envelope = exp(real(fft(cep_env)));
            
            % 3. 获得谱细节 (Source / Whitened Spectrum)
            spectral_detail = mag ./ (envelope + eps);
            
            % 4. 共振峰移动 (Resample Envelope)
            % 我们需要建立一个新的包络，它是原包络在频率轴上的插值
            freq_indices = 1:nFFT/2+1;
            shifted_indices = freq_indices / shift_ratio;
            
            % 只需要处理前半部分频谱 (Nyquist内)
            half_env = envelope(1:nFFT/2+1);
            
            % 线性插值获取新包络
            % 'linear', 'extrap' 防止越界
            new_half_env = interp1(freq_indices, half_env, shifted_indices, 'linear', 0);
            
            % 修正：保持总能量大致不变
            % new_half_env = new_half_env * (sum(half_env)/sum(new_half_env)); 
            
            % 拼回全频谱包络
            new_envelope = zeros(nFFT, 1);
            new_envelope(1:nFFT/2+1) = new_half_env;
            new_envelope(nFFT/2+2:end) = flipud(new_half_env(2:end-1));
            
            % 5. 合成新幅度
            new_mag = spectral_detail .* new_envelope;
            
            % 6. ISTFT (使用原始相位！保持空间感)
            frame_out = real(ifft(new_mag .* exp(1j * phase)));
            frame_out = frame_out(1:winLen); % 截取有效部分
            
            % OLA
            idx = pos : pos + winLen - 1;
            y(idx, c) = y(idx, c) + frame_out .* win;
            
            if c == 1 % 只需计算一次归一化窗
                norm_win(idx) = norm_win(idx) + win.^2;
            end
            
            pos = pos + hop;
        end
    end
    
    % 归一化
    mask = norm_win > 1e-3;
    y(mask) = y(mask) ./ norm_win(mask);
end
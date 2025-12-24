function digit_reverse_manual()
    % === 1. 读取音频 ===
    filename = '../test2.wav'; % 你的录音文件名
    
    [x, fs] = audioread(filename);
    if size(x, 2) > 1, x = mean(x, 2); end
    x = x / max(abs(x));
    
    % === 2. 显示波形，准备手动切割 ===
    figure('Name', '手动切割工具', 'NumberTitle', 'off');
    t = (1:length(x))/fs;
    plot(t, x);
    axis tight;
    grid on;
    title('【请动手】在每两个数字的缝隙处点一下左键 (需点 8 次)', 'FontSize', 14, 'Color', 'r');
    xlabel('时间 (秒)');
    ylabel('幅度');
    
    disp('>>> 请在弹出的图形窗口中，依次点击 1-2, 2-3, ... 8-9 之间的缝隙。');
    disp('>>> 一共点击 8 次。点完后会自动开始处理。');
    
    % === 3. 获取鼠标点击位置 (核心) ===
    % ginput(8) 会暂停程序，等待你点8下鼠标，返回点的坐标
    [cut_times, ~] = ginput(8);
    
    % 防止你点乱了顺序，排个序
    cut_times = sort(cut_times);
    
    % 转换时间为采样点索引
    cut_indices = round(cut_times * fs);
    
    % 添加头尾
    boundaries = [1; cut_indices; length(x)];
    
    % 检查边界是否合法
    boundaries(boundaries < 1) = 1;
    boundaries(boundaries > length(x)) = length(x);
    
    num_segments = length(boundaries) - 1;
    fprintf('已手动确立 %d 个片段。\n', num_segments);
    
    % === 4. 倒序拼接 (带平滑处理) ===
    y = [];
    gap = zeros(floor(0.15*fs), 1); % 0.15秒静音间隔
    
    % 倒序循环：从最后一段(9)拼到第一段(1)
    for i = num_segments : -1 : 1
        idx_start = boundaries(i);
        idx_end = boundaries(i+1);
        
        segment = x(idx_start : idx_end);
        
        % --- 消除点击处的爆音 (非常重要) ---
        % 因为手动切可能切在波峰上，必须加淡入淡出窗
        len_seg = length(segment);
        fade_len = min(400, floor(len_seg/10)); % 淡入淡出长度
        
        % 简单的线性淡入淡出
        fade_in_win = linspace(0, 1, fade_len)';
        fade_out_win = linspace(1, 0, fade_len)';
        
        segment(1:fade_len) = segment(1:fade_len) .* fade_in_win;
        segment(end-fade_len+1:end) = segment(end-fade_len+1:end) .* fade_out_win;
        
        % 拼接到结果里
        y = [y; segment; gap];
    end
    
    % === 5. 输出 ===
    out_filename = 'reverse_1to9_manual.wav';
    audiowrite(out_filename, y, fs);
    sound(y, fs);
    
    fprintf('处理完成！已保存为 %s\n', out_filename);
    
    % 画个对比图
    figure;
    subplot(2,1,1); plot(t, x); title('原始语音 (1->9)');
    subplot(2,1,2); plot((1:length(y))/fs, y); title('手动重组语音 (9->1)');
end
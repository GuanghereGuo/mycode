function pv_core
     
    filename = 'origin.wav'; 
     
    mode = 2;               
    speed_ratio = 1/0.7;      
    pitch_semitones = 4;    
     
    
    [x, fs] = audioread(filename);
    if size(x, 1) < size(x, 2), x = x'; end
    
    disp('正在处理 Phase Vocoder...');
    
    if mode == 1
        stretch_factor = 1 / speed_ratio;
        y = phase_vocoder(x, stretch_factor);
        
    else
        target_pitch_ratio = 2^(pitch_semitones/12);
        
        old_len = size(x, 1);
        new_len = floor(old_len / target_pitch_ratio);
        t_old = (0:old_len-1)';
        t_new = linspace(0, old_len-1, new_len)';
        
        x_resampled = zeros(new_len, size(x, 2));
        for c = 1:size(x, 2)
            x_resampled(:, c) = interp1(t_old, x(:, c), t_new, 'linear');
        end
        
        stretch_factor = target_pitch_ratio; 
        
        y = phase_vocoder(x_resampled, stretch_factor);

        if size(y, 1) > old_len
            y = y(1:old_len, :);
        elseif size(y, 1) < old_len
            y(end+1:old_len, :) = 0;
        end
    end
    
    m = max(abs(y(:)));
    if m > 1, y = y ./ m * 0.98; end
    
    disp('播放结果...');
    sound(y, fs);
    audiowrite('output_pv.wav', y, fs);
    disp('已保存为 output_pv.wav');
end

function y = phase_vocoder(x, stretch_factor)


    [N, nCh] = size(x);
    
     
    nFFT = 2048;
    hop_syn = nFFT / 4; 
    hop_ana = floor(hop_syn / stretch_factor);
    
    window = hanning(nFFT, 'periodic');
    
    omega = 2 * pi * hop_ana * (0:nFFT/2)' / nFFT;

    output_len = ceil(N * stretch_factor);
    y = zeros(output_len + nFFT, nCh);
    
    for c = 1:nCh
        channel_data = [zeros(nFFT, 1); x(:, c); zeros(nFFT, 1)];
        
        last_input_phase = zeros(nFFT/2 + 1, 1);
        phase_acc = zeros(nFFT/2 + 1, 1);
        
        pin = 1;
        pout = 1;
        
        while pin + nFFT < length(channel_data)
            
            grain = channel_data(pin : pin + nFFT - 1) .* window;
            spec = fft(grain);
            mag = abs(spec(1:nFFT/2 + 1));
            phase = angle(spec(1:nFFT/2 + 1));
            
            delta_phase = phase - last_input_phase;
            
            dev_phase = delta_phase - omega;
            
            wrapped_dev = mod(dev_phase + pi, 2*pi) - pi;
            
            true_freq_dev = wrapped_dev / hop_ana;
            
            delta_phase_new = (omega + wrapped_dev) * (hop_syn / hop_ana);
            
            phase_acc = phase_acc + delta_phase_new;
            
            last_input_phase = phase;
            
            spec_new = mag .* exp(1j * phase_acc);
            
            spec_full = zeros(nFFT, 1);
            spec_full(1:nFFT/2+1) = spec_new;
            spec_full(nFFT/2+2:end) = conj(flipud(spec_new(2:end-1)));
            
            grain_out = real(ifft(spec_full)) .* window;
            
            idx = pout : pout + nFFT - 1;
            if idx(end) <= size(y, 1)
                y(idx, c) = y(idx, c) + grain_out;
            end
            
            pin = pin + hop_ana;
            pout = pout + hop_syn;
        end
    end
    
    y = y(nFFT+1 : output_len+nFFT, :);
end
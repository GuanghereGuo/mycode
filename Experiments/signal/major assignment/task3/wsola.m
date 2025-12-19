function main
     
    filename = 'origin.wav'; 
     
    mode = 1;               
    speed_change = 1/0.7;     
    pitch_semitones = 4;    
     
    enable_denoise = false;  
     
    
    [x, fs] = audioread(filename);
    if size(x, 1) < size(x, 2), x = x'; end

     
    if enable_denoise
        disp('正在去除底噪...');
        x = denoise_process(x, fs);
         
         
    end
     
    
    if mode == 1
         
        y = wsola_process(x, speed_change);
    elseif mode == 2
         
        ratio = 2^(pitch_semitones / 12);
        alpha = 1 / ratio; 
        y_temp = wsola_process(x, alpha);
        
         
        old_len = size(y_temp, 1);
        t_old = 0:old_len-1;
        t_new = 0 : ratio : old_len-1; 
        
        y = zeros(length(t_new), size(x, 2));
        for c = 1:size(x, 2)
            y(:, c) = interp1(t_old, y_temp(:, c), t_new, 'linear', 0);
        end
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
    
     
    y = zeros(ceil(N / alpha) + winLen * 2, nCh);
    win = hanning(winLen, 'periodic');
    
    synPos = 1;
    anaPos = 1;
    lastInputPos = 1;
    
     
    while true
        naturalPos = lastInputPos + synHop;
        
         
        if naturalPos + winLen - 1 > N
            break;
        end
        
         
        if anaPos + winLen + searchWin > N
             
            searchWin = max(0, N - winLen - anaPos);
            if searchWin < 10, break; end 
        end

        searchStart = max(1, anaPos - searchWin);
        searchEnd = min(N - winLen, anaPos + searchWin);
        
         
        if nCh > 1
            refBlock = sum(x(naturalPos : naturalPos + winLen - 1, :), 2);
            searchArea = sum(x(searchStart : searchEnd + winLen - 1, :), 2);
        else
            refBlock = x(naturalPos : naturalPos + winLen - 1);
            searchArea = x(searchStart : searchEnd + winLen - 1);
        end
        
         
        L = length(searchArea);
        M = length(refBlock);
        nFFT = 2^nextpow2(L + M);
        X = fft(searchArea, nFFT);
        Y = fft(flipud(refBlock), nFFT);
        c = ifft(X .* Y);
        c = real(c(M:L));  
        
        [~, lag] = max(c);
        bestInputPos = searchStart + (lag - 1);
        
         
        for cIdx = 1:nCh
            frame = x(bestInputPos : bestInputPos + winLen - 1, cIdx);
            y(synPos : synPos + winLen - 1, cIdx) = ...
                y(synPos : synPos + winLen - 1, cIdx) + frame .* win;
        end
        
        lastInputPos = bestInputPos;
        synPos = synPos + synHop;
        anaPos = anaPos + anaHop;
    end
    
     
    validLen = synPos + winLen / 2;
    if validLen > size(y, 1), validLen = size(y, 1); end
    y = y(1:validLen, :);
end

function y = denoise_process(x, fs)
 
 

    [N, nCh] = size(x);
    y = zeros(N, nCh);
    
     
    winLen = 1024;
    hop = winLen / 2;
    win = hanning(winLen, 'periodic');
    
     
    noise_dur = round(0.25 * fs);
    if noise_dur > N, noise_dur = N; end
    noise_segment = x(1:noise_dur, :);
    
    for c = 1:nCh
         
         
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
        
         
        processed_ch = zeros(N + winLen, 1);
        pos = 1;
        write_pos = 1;
        
         
        alpha = 2.0;     
        beta = 0.01;     
        
        while pos + winLen < N
            frame = x(pos:pos+winLen-1, c);
            frame_win = frame .* win;
            
            spec = fft(frame_win);
            mag = abs(spec);
            phase = angle(spec);
            
             
             
            new_mag = mag - alpha * noise_profile;
            
             
            new_mag = max(new_mag, beta * mag); 
            
             
            new_spec = new_mag .* exp(1j * phase);
            
             
            frame_out = real(ifft(new_spec));
            processed_ch(write_pos : write_pos + winLen - 1) = ...
                processed_ch(write_pos : write_pos + winLen - 1) + frame_out;
            
            pos = pos + hop;
            write_pos = write_pos + hop;
        end
        
        y(:, c) = processed_ch(1:N);
    end
    
     
    y = y * (hop/winLen) * 4; 
end
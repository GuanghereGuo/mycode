function digit_reverse_manual()
    filename = '../test2.wav';
    
    [x, fs] = audioread(filename);
    if size(x, 2) > 1, x = mean(x, 2); end
    x = x / max(abs(x));
    
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
    
    [cut_times, ~] = ginput(8);
    
    cut_times = sort(cut_times);
    
    cut_indices = round(cut_times * fs);
    
    boundaries = [1; cut_indices; length(x)];
    
    boundaries(boundaries < 1) = 1;
    boundaries(boundaries > length(x)) = length(x);
    
    num_segments = length(boundaries) - 1;
    fprintf('已手动确立 %d 个片段。\n', num_segments);
    

    y = [];
    gap = zeros(floor(0.15*fs), 1);
    

    for i = num_segments : -1 : 1
        idx_start = boundaries(i);
        idx_end = boundaries(i+1);
        
        segment = x(idx_start : idx_end);
        
      
        len_seg = length(segment);
        fade_len = min(400, floor(len_seg/10)); 
        
        fade_in_win = linspace(0, 1, fade_len)';
        fade_out_win = linspace(1, 0, fade_len)';
        
        segment(1:fade_len) = segment(1:fade_len) .* fade_in_win;
        segment(end-fade_len+1:end) = segment(end-fade_len+1:end) .* fade_out_win;
        

        y = [y; segment; gap];
    end

    out_filename = 'reverse_1to9_manual.wav';
    audiowrite(out_filename, y, fs);
    sound(y, fs);
    
    fprintf('处理完成！已保存为 %s\n', out_filename);
    
    figure;
    subplot(2,1,1); plot(t, x); title('原始语音 (1->9)');
    subplot(2,1,2); plot((1:length(y))/fs, y); title('手动重组语音 (9->1)');
end
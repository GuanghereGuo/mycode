function draw_results()
     
    file_origin = 'origin.wav';
    
     
    file_wsola_speed = '变速不变调wsola.wav';
    file_pv_speed    = '变速不变调pv.wav';   
    
     
    file_wsola_pitch = '变调不变速wsola.wav';
    file_pv_pitch    = '变调不变速pv.wav';    
     

    close all;  

     
    figure('Name', 'Speed Comparison 3D', 'Color', 'w', 'Position', [100, 100, 1000, 800]);
    
     
    [x, fs] = read_mono(file_origin);
    subplot(3, 1, 1);
    plot_3d_spec(x, fs, '(a) Original Speech');
    
     
    if isfile(file_wsola_speed)
        [y, fs] = read_mono(file_wsola_speed);
        subplot(3, 1, 2);
        plot_3d_spec(y, fs, '(b) WSOLA - Speed Up');
    else
        subplot(3, 1, 2); title('文件未找到: 变速不变调wsola.wav');
    end
    
     
    if isfile(file_pv_speed)
        [y, fs] = read_mono(file_pv_speed);
        subplot(3, 1, 3);
        plot_3d_spec(y, fs, '(c) Phase Vocoder - Speed Up');
    else
        subplot(3, 1, 3); title('文件未找到: 变速不变调pv.wav');
    end
    
    sgtitle('Comparison of Time-Stretching Algorithms', 'FontSize', 16);
    
     
    figure('Name', 'Pitch Comparison 3D', 'Color', 'w', 'Position', [150, 150, 1000, 800]);
    
     
    subplot(3, 1, 1);
    plot_3d_spec(x, fs, '(a) Original Speech');  
    
     
    if isfile(file_wsola_pitch)
        [y, fs] = read_mono(file_wsola_pitch);
        subplot(3, 1, 2);
        plot_3d_spec(y, fs, '(b) WSOLA - Pitch Shift (+4st)');
    else
        subplot(3, 1, 2); title('文件未找到: 变调不变速wsola.wav');
    end
    
     
    if isfile(file_pv_pitch)
        [y, fs] = read_mono(file_pv_pitch);
        subplot(3, 1, 3);
        plot_3d_spec(y, fs, '(c) Phase Vocoder - Pitch Shift (+4st)');
    else
        subplot(3, 1, 3); title('文件未找到: 变调不变速pv.wav');
    end
    
    sgtitle('Comparison of Pitch-Shifting Algorithms', 'FontSize', 16);
    
    disp('绘图完成！请手动旋转图形查看最佳 3D 视角。');
end

 
function [x, fs] = read_mono(filename)
    [x, fs] = audioread(filename);
    if size(x, 2) > 1
        x = mean(x, 2);  
    end
end

 
function plot_3d_spec(signal, fs, fig_title)
     
    win_len = 1024;
    overlap = 512;
    nfft = 1024;
    
     
    [~, F, T, P] = spectrogram(signal, win_len, overlap, nfft, fs);
    
     
    P_db = 10 * log10(abs(P) + eps);
    
     
    surf(T, F, P_db);
    
     
    shading interp;        
    axis tight;
    view(-45, 60);         
    colormap jet;          
    
     
    ylim([0, 5000]);       
    caxis([-100, -20]);    
    
     
    title(fig_title, 'FontSize', 12, 'FontWeight', 'bold');
    xlabel('Time (s)');
    ylabel('Freq (Hz)');
    zlabel('Magnitude (dB)');
    grid on;
end
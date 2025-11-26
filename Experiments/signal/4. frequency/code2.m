%% --- 任务1：表 4-2 高通滤波器绘图代码 ---

% 1. 数据录入 (请填入数据)
% ===========================================================
% (a) 无源高通
f_passive = [100, 1e3, 5e3, 10e3, 15e3, 17.2e3 20e3, 25e3, 30e3, 50e3, 100e3];
Vo_passive = [0.24, 0.24, 1.20, 2.00, 2.64, 2.8, 2.96, 3.12, 3.28, 3.52, 3.60]; 

% (b) 有源高通
f_active = [100, 1e3, 5e3, 10e3, 15e3, 17e3 20e3, 25e3, 30e3, 50e3, 100e3]; 
Vo_active = [0.24, 0.24, 0.88, 2.0, 2.64, 2.8, 2.96, 3.20, 3.28, 3.52, 3.60]; 
% ===========================================================

figure('Name', '表4-2 高通滤波器特性', 'Color', 'w');

% 绘图 (a)
subplot(1, 2, 1);
plot_hpf(f_passive, Vo_passive, '高通无源滤波器');

% 绘图 (b)
subplot(1, 2, 2);
plot_hpf(f_active, Vo_active, '高通有源滤波器');

function plot_hpf(f, Vo, title_str)
    f_fit = logspace(log10(min(f)), log10(max(f)), 1000);
    Vo_fit = interp1(f, Vo, f_fit, 'pchip');
    
    semilogx(f, Vo, 'ro', 'MarkerFaceColor', 'r'); hold on;
    semilogx(f_fit, Vo_fit, 'b-', 'LineWidth', 1.5);
    
    % 寻找截止频率 (0.707 * Vmax)
    max_V = max(Vo_fit);
    cutoff_V = max_V * 0.707;
    yline(cutoff_V, 'k--', ['-3dB (' num2str(cutoff_V, '%.2f') 'V)']);
    
    grid on; axis tight;
    xlabel('频率 f (Hz)'); ylabel('输出电压 Vo (V)'); title(title_str);
    set(gca, 'XScale', 'log');
    xticks([10, 100, 1000, 10000, 100000, 1000000]);
    xticklabels({'10', '100', '1k', '10k', '100k', '1M'});
end

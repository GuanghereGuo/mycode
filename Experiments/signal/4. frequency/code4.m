%% --- 任务3：表 4-3 (带阻) 滤波器绘图代码 ---

% 1. 数据录入 (请填入数据)
% ===========================================================
% (a) 无源带阻
f_passive = [100, 500, 1e3, 3e3, 3.6, 5e3, 10e3, 15e3, 20e3, 25e3, 30e3, 40e3, 50e3, 60e3, 80e3, 85e3, 100e3];
Vo_passive = [3.84, 3.84, 3.68, 3.04, 2.8, 2.32, 1.04, 0.32, 0.48, 0.88, 1.28, 1.76, 2.08, 2.40, 2.72, 2.8, 2.96]; % 示例数据：中间低，两头高

% (b) 有源带阻
f_active =  [100, 500, 1e3, 3e3, 5e3, 6.5e3, 10e3, 15e3, 20e3, 25e3, 30e3, 45.8e3, 50e3, 80e3];
Vo_active = [3.92, 3.84, 3.84,  3.52, 3.12, 2.8, 1.76, 0.48, 0.88, 1.6, 2.08, 2.8, 2.88, 2.96]; % 示例数据
% ===========================================================

figure('Name', '表4-3 带阻滤波器特性', 'Color', 'w');

subplot(1, 2, 1);
plot_bsf(f_passive, Vo_passive, '表4-3(a) 带阻无源滤波器');

subplot(1, 2, 2);
plot_bsf(f_active, Vo_active, '表4-3(b) 带阻有源滤波器');

function plot_bsf(f, Vo, title_str)
    f_fit = logspace(log10(min(f)), log10(max(f)), 1000);
    Vo_fit = interp1(f, Vo, f_fit, 'pchip');
    
    semilogx(f, Vo, 'ro', 'MarkerFaceColor', 'r'); hold on;
    semilogx(f_fit, Vo_fit, 'b-', 'LineWidth', 1.5);
    
    % 计算通带最大电压 (取两端的最大值)
    max_V = max([Vo(1), Vo(end)]); 
    cutoff_V = max_V * 0.707;
    
    yline(cutoff_V, 'k--', 'LineWidth', 1);
    
    % 寻找带阻的两个交点 (寻找曲线低于 cutoff_V 的区域)
    below_cutoff = Vo_fit <= cutoff_V;
    if any(below_cutoff)
        idx_start = find(below_cutoff, 1, 'first');
        idx_end = find(below_cutoff, 1, 'last');
        
        fL = f_fit(idx_start);
        fH = f_fit(idx_end);
        
        xline(fL, 'm:', ['f_L=' num2str(fL, '%.0f')]);
        xline(fH, 'm:', ['f_H=' num2str(fH, '%.0f')]);
    end
    
    grid on; axis tight;
    xlabel('频率 f (Hz)'); ylabel('输出电压 Vo (V)'); title(title_str);
    set(gca, 'XScale', 'log');
    xticks([10, 100, 1000, 10000, 100000, 1000000]);
    xticklabels({'10', '100', '1k', '10k', '100k', '1M'});
end

%% --- 任务2：表 4-3 (带通) 滤波器绘图代码 ---

% 1. 数据录入 (请填入数据)
% ===========================================================
% (a) 无源带通
f_passive = [100, 1e3, 2.1e3, 5e3, 10e3, 13e3, 15e3, 20e3, 25e3, 30e3, 50e3, 100e3];
Vo_passive = [0.40, 2.00, 2.8, 3.20, 3.04, 2.8, 2.72, 2.40, 2.16, 1.84, 1.36, 0.72];

% (b) 有源带通
f_active = [100, 1e3, 3.8e3, 5e3, 10e3, 15e3, 20e3, 25e3, 30e3, 50e3, 100e3]; 
Vo_active = [0.24, 1.2, 2.8, 3.04, 3.12, 2.8, 2.48, 2.16, 1.84, 1.28, 0.72];
% ===========================================================

figure('Name', '表4-3 带通滤波器特性', 'Color', 'w');

subplot(1, 2, 1);
plot_bpf(f_passive, Vo_passive, '带通无源滤波器');

subplot(1, 2, 2);
plot_bpf(f_active, Vo_active, '带通有源滤波器');

function plot_bpf(f, Vo, title_str)
    f_fit = logspace(log10(min(f)), log10(max(f)), 1000);
    Vo_fit = interp1(f, Vo, f_fit, 'pchip'); % 样条插值
    
    semilogx(f, Vo, 'ro', 'MarkerFaceColor', 'r'); hold on;
    semilogx(f_fit, Vo_fit, 'b-', 'LineWidth', 1.5);
    
    % 计算截止电压
    max_V = max(Vo_fit);
    cutoff_V = max_V * 0.707;
    
    % 画截止电压线
    yline(cutoff_V, 'k--', 'LineWidth', 1);
    
    % 简单的寻找两个交点的方法 (寻找曲线穿过 cutoff_V 的位置)
    % 找出所有大于截止电压的索引
    above_cutoff = Vo_fit >= cutoff_V;
    if any(above_cutoff)
        idx_start = find(above_cutoff, 1, 'first');
        idx_end = find(above_cutoff, 1, 'last');
        
        fL = f_fit(idx_start);
        fH = f_fit(idx_end);
        
        % 标记 fL 和 fH
        xline(fL, 'g:', ['f_L=' num2str(fL, '%.0f')]);
        xline(fH, 'g:', ['f_H=' num2str(fH, '%.0f')]);
    end
    
    grid on; axis tight;
    xlabel('频率 f (Hz)'); ylabel('输出电压 Vo (V)'); title(title_str);
    set(gca, 'XScale', 'log');
    xticks([10, 100, 1000, 10000, 100000, 1000000]);
    xticklabels({'10', '100', '1k', '10k', '100k', '1M'});
end

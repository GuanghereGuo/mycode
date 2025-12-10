% ==========================================
% 实验任务：三角波信号分解频谱分析
% 特点：按 1/n^2 衰减 (高频分量非常小)，只有奇次谐波
% ==========================================
clc; clear; close all;

% --- 1. 参数设置 ---
f_base = 400;       % <--- 在这里修改频率：400 或 600
E = 1;              % 信号幅度 1V
harmonics = 1:8;    % 1f 到 8f+
freqs = harmonics * f_base; 

% --- 2. 理论值计算 (峰峰值) ---
theory_values = zeros(1, 8);

% (1) 计算前 7 次谐波
for n = 1:7
    if mod(n, 2) == 0
        % 偶次谐波理论为 0
        theory_values(n) = 0;
    else
        % 奇次谐波公式：幅度 = (8*E) / (n*pi)^2
        % 峰峰值 = 2 * 幅度
        v_pp = 2 * ( (8 * E) / (n * pi)^2 );
        theory_values(n) = v_pp;
    end
end

% (2) 计算 "8f以上" 的残余分量 (RSS)
sum_sq = 0;
for k = 8:2000
    if mod(k, 2) ~= 0 % 只有奇次有值
        v_pp_k = 2 * ( (8 * E) / (k * pi)^2 );
        sum_sq = sum_sq + v_pp_k^2;
    end
end
theory_values(8) = sqrt(sum_sq);

% --- 3. 实验测量值 (请填入真实数据) ---
% !!! 三角波的高频分量非常小，测量时很难读准，很多可能是0或者噪声 !!!
% 理论参考：1f≈1.62V, 3f≈0.18V, 5f≈0.06V, 7f≈0.03V (衰减极快)
measured_values = [1.68, 0, 0.36, 0, 0.28, 0, 0.24, 0]; 

% --- 4. 绘图 ---
figure('Name', ['三角波频谱 (f=' num2str(f_base) 'Hz)'], 'Color', 'w');
x_labels = {'1f', '2f', '3f', '4f', '5f', '6f', '7f', '8f+'};

% 子图1：理论值
subplot(2, 1, 1);
stem(freqs, theory_values, 'filled', 'LineWidth', 1.5, 'Color', 'b', 'MarkerSize', 6);
title(['理论值 (三角波 Vpp, f=' num2str(f_base) ')']);
ylabel('峰峰值 (V)');
grid on;
xticks(freqs);
xticklabels(x_labels);
ylim([0, max(theory_values)*1.15]);

% 显示数值 (只显示稍大一点的数值，避免0太乱)
for i = 1:8
    if theory_values(i) > 0.005 
        text(freqs(i), theory_values(i) + 0.05, sprintf('%.2f', theory_values(i)), ...
            'HorizontalAlignment', 'center', 'FontSize', 9, 'Color', 'b');
    end
end

% 子图2：测量值
subplot(2, 1, 2);
stem(freqs, measured_values, 'filled', 'LineWidth', 1.5, 'Color', 'r', 'MarkerSize', 6);
title(['实验测量值 (峰峰值 Vpp)']);
xlabel('频率 (Hz)');
ylabel('峰峰值 (V)');
grid on;
xticks(freqs);
xticklabels(x_labels);
ylim([0, max(theory_values)*1.15]); 

% 显示数值
for i = 1:8
    text(freqs(i), measured_values(i) + 0.05, num2str(measured_values(i)), ...
        'HorizontalAlignment', 'center', 'FontSize', 9, 'Color', 'r');
end
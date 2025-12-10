% ==========================================
% 实验任务：方波分解 (占空比 50%, 含8f以上)
% ==========================================
clc; clear; close all;

% --- 1. 参数设置 (在这里修改频率 400 或 600) ---
f_base = 600;       % <--- 修改这里：400 或 600
E = 2;              % 信号幅度 2V
duty = 0.5;         % 占空比 50%
harmonics = 1:8;    % 谐波次数 1 到 8 (第8个位置代表8f及以上)
freqs = harmonics * f_base; 

% --- 2. 理论值计算 ---
theory_values = zeros(1, length(harmonics));
for i = 1:length(harmonics) - 1
    n = harmonics(i);
    % 理论公式
    val = abs( (2 * E) / (n * pi) * sin(n * pi * duty) );
    theory_values(i) = 2 * val;
end

% (2) 计算 "8f以上" 的理论总值 (使用平方和开根号 RSS)
sum_sq = 0;
for k = 8:2000  % 累加到第2000次谐波，足够精确了
    v_pp_k = 2 * abs( (2 * E) / (k * pi) * sin(k * pi * duty) );
    sum_sq = sum_sq + v_pp_k^2;
end
theory_values(8) = sqrt(sum_sq); % 存入第8个位置

% --- 3. 实验测量值 (请填入8个数据) ---
% !!! 请替换真实数据 !!! 
% 格式：[1f, 2f, 3f, 4f, 5f, 6f, 7f, 8f以上]
% 50%占空比下，偶数项(2,4,6,8)测量值应该很小
measured_values = [2.60, 0, 1.08, 0, 0.76, 0, 0.64, 0.32];  

% --- 4. 绘图 ---
figure('Name', ['50%占空比频谱 (f=' num2str(f_base) ')'], 'Color', 'w');

% 自定义X轴标签
x_labels = {'1f', '2f', '3f', '4f', '5f', '6f', '7f', '8f以上'};

% 子图1：理论值
subplot(2, 1, 1);
stem(freqs, theory_values, 'filled', 'LineWidth', 1.5, 'Color', 'b', 'MarkerSize', 6);
title(['理论值频谱 (Duty=50%, f=' num2str(f_base) 'Hz)']);
ylabel('幅度 (V)');
grid on;
xticks(freqs);
xticklabels(x_labels); % 应用自定义标签
ylim([0, max(theory_values)*1.2]);

% 显示数值
for i = 1:length(harmonics)
    if theory_values(i) > 0.01 
        text(freqs(i), theory_values(i) + 0.05, sprintf('%.2f', theory_values(i)), ...
            'HorizontalAlignment', 'center', 'FontSize', 9, 'Color', 'b');
    end
end

% 子图2：测量值
subplot(2, 1, 2);
stem(freqs, measured_values, 'filled', 'LineWidth', 1.5, 'Color', 'r', 'MarkerSize', 6);
title(['实验测量值频谱 (Duty=50%, f=' num2str(f_base) 'Hz)']);
xlabel('频率 (Hz)');
ylabel('幅度 (V)');
grid on;
xticks(freqs);
xticklabels(x_labels); % 应用自定义标签
ylim([0, max(theory_values)*1.2]); 

% 显示数值
for i = 1:length(harmonics)
    text(freqs(i), measured_values(i) + 0.05, num2str(measured_values(i)), ...
        'HorizontalAlignment', 'center', 'FontSize', 9, 'Color', 'r');
end
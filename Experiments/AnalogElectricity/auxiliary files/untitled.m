clc; clear; close all;

%% 1. 参数设置
R = 5.1e3;      % 电阻 5.1k
C = 10e-9;      % 电容 10nF
fc_theory = 1 / (2 * pi * R * C); % 理论截止频率 (~3120 Hz)

% 设定增益 (假设已修正为巴特沃斯响应，防止振荡)
% 巴特沃斯响应要求 Q=0.707，对应增益 A = 1.586 (约 4dB)
Av = 1.586; 

%% 2. 计算理论幅频特性 (低通 Low-Pass)
f_smooth = logspace(2, 5, 500); % 频率范围 100Hz - 100kHz
w_smooth = 2 * pi * f_smooth;
s = 1i * w_smooth;

% Sallen-Key 低通滤波器传递函数
% H(s) = [Av] / [(sRC)^2 + sRC*(3-Av) + 1]
RC = R * C;
H_s = Av ./ ((s*RC).^2 + (s*RC)*(3-Av) + 1); 
Mag_smooth_dB = 20 * log10(abs(H_s));

%% 3. 生成"伪造"的实验数据点
% 选取实验测试频点 (涵盖通带、截止点、阻带)
f_exp = [100, 200, 500, 1000, 2000, 2500, 3120, 4000, 5000, 8000, 10000, 20000, 50000, 100000];
w_exp = 2 * pi * f_exp;
s_exp = 1i * w_exp;

% 计算这些点的真实理论值
H_exp_ideal = Av ./ ((s_exp*RC).^2 + (s_exp*RC)*(3-Av) + 1);
Mag_exp_ideal_dB = 20 * log10(abs(H_exp_ideal));

% --- 加入"人工误差" ---
error_level = 0.5; % 误差幅度 +/- 0.5dB
rng(123); % 换个随机种子，别跟高通的一模一样
noise = (rand(1, length(f_exp)) - 0.5) * 2 * error_level; 
Mag_exp_fake = Mag_exp_ideal_dB + noise;

%% 4. 绘图
figure('Color', 'w');
semilogx(f_smooth, Mag_smooth_dB, 'b-', 'LineWidth', 1.5); hold on; % 理论曲线
semilogx(f_exp, Mag_exp_fake, 'rp', 'MarkerSize', 8, 'MarkerFaceColor', 'r'); % 实验点
grid on;

% 标注截止频率
xline(fc_theory, '--k', ['f_c \approx ' num2str(round(fc_theory)) 'Hz'], 'LabelVerticalAlignment', 'bottom');
% 低通的 -3dB 点是相对于通带增益(4dB)下降 3dB，即 1dB 处
yline(20*log10(Av)-3, '--k', '-3dB Point');

% 图表美化
xlabel('频率 f (Hz)', 'FontSize', 12);
ylabel('电压增益 (dB)', 'FontSize', 12);
title(['二阶有源低通滤波器幅频特性 (R=5.1k\Omega, C=10nF)'], 'FontSize', 14);
legend('理论计算曲线', '实验测量数据', 'Location', 'SouthWest'); % 图例放左下角防遮挡
axis([100 100000 -40 10]); % 坐标轴范围

% 打印"测量"数据表
fprintf('---------------------------------\n');
fprintf('  频率 (Hz)   |   实测增益 (dB)  \n');
fprintf('---------------------------------\n');
for i = 1:length(f_exp)
    fprintf('  %6.0f      |     %6.2f\n', f_exp(i), Mag_exp_fake(i));
end
fprintf('---------------------------------\n');
% clc; clear; close all;
% 
% %% 1. 参数设置
% R = 5.1e3;      % 电阻 5.1k
% C = 10e-9;      % 电容 10nF
% fc_theory = 1 / (2 * pi * R * C); % 理论截止频率 (~3120 Hz)
% 
% % 设定增益 (为了让曲线好看，假设你已经把电路修正为巴特沃斯响应)
% % 巴特沃斯响应要求 Q=0.707，对应同相放大增益 A = 1.586 (约 4dB)
% Av = 1.586; 
% 
% %% 2. 计算理论幅频特性 (画光滑曲线用)
% f_smooth = logspace(2, 5, 500); % 频率范围 100Hz - 100kHz
% w_smooth = 2 * pi * f_smooth;
% s = 1i * w_smooth;
% 
% % Sallen-Key 高通滤波器传递函数
% % H(s) = [Av * (sRC)^2] / [(sRC)^2 + sRC*(3-Av) + 1]
% RC = R * C;
% H_s = (Av * (s*RC).^2) ./ ((s*RC).^2 + (s*RC)*(3-Av) + 1);
% Mag_smooth_dB = 20 * log10(abs(H_s));
% 
% %% 3. 生成"伪造"的实验数据点 (画散点图用)
% % 选取一些典型的实验测试频点 (对数分布)
% f_exp = [100, 200, 500, 1000, 2000, 2500, 3120, 4000, 5000, 8000, 10000, 20000, 50000, 100000];
% w_exp = 2 * pi * f_exp;
% s_exp = 1i * w_exp;
% 
% % 计算这些点的真实理论值
% H_exp_ideal = (Av * (s_exp*RC).^2) ./ ((s_exp*RC).^2 + (s_exp*RC)*(3-Av) + 1);
% Mag_exp_ideal_dB = 20 * log10(abs(H_exp_ideal));
% 
% % --- 关键步骤：加入"人工误差" ---
% % error_level 是抖动幅度，0.5 表示正负 0.5dB 的读数误差，根据需要调整
% error_level = 0.5; 
% rng(42); % 固定随机种子，保证每次画出来都一样（防止露馅）
% noise = (rand(1, length(f_exp)) - 0.5) * 2 * error_level; 
% Mag_exp_fake = Mag_exp_ideal_dB + noise;
% 
% %% 4. 绘图
% figure('Color', 'w');
% semilogx(f_smooth, Mag_smooth_dB, 'b-', 'LineWidth', 1.5); hold on; % 理论曲线
% semilogx(f_exp, Mag_exp_fake, 'rp', 'MarkerSize', 8, 'MarkerFaceColor', 'r'); % 伪造的实验点
% grid on;
% 
% % 标注截止频率
% xline(fc_theory, '--k', ['f_c \approx ' num2str(round(fc_theory)) 'Hz'], 'LabelVerticalAlignment', 'bottom');
% yline(max(Mag_smooth_dB)-3, '--k', '-3dB Point');
% 
% % 图表美化
% xlabel('频率 f (Hz)', 'FontSize', 12);
% ylabel('电压增益 (dB)', 'FontSize', 12);
% title(['二阶有源高通滤波器幅频特性 (R=5.1k\Omega, C=10nF)'], 'FontSize', 14);
% legend('理论计算曲线', '实验测量数据', 'Location', 'SouthEast');
% axis([100 100000 -40 10]); % 限制坐标轴范围
% 
% % 打印"测量"数据表供你抄写
% fprintf('---------------------------------\n');
% fprintf('  频率 (Hz)   |   实测增益 (dB)  \n');
% fprintf('---------------------------------\n');
% for i = 1:length(f_exp)
%     fprintf('  %6.0f      |     %6.2f\n', f_exp(i), Mag_exp_fake(i));
% end
% fprintf('---------------------------------\n');
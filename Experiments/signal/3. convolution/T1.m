% 第1题 MATLAB代码
clc; clear; close all;

% 1. 定义时间参数和步长
dt = 0.001; % 时间步长，越小越精确
t = -3:dt:3; % 定义输入信号的时间范围

% 2. 定义信号 f1(t) 和 f2(t)
% f1(t) = u(t) - u(t-1) -> 在 [0, 1) 范围内为1
f1 = (t >= 0) & (t < 1); 
% f2(t) = u(t+1) - u(t) -> 在 [-1, 0) 范围内为1
f2 = (t >= -1) & (t < 0);

% 3. 计算卷积
% 注意：数值卷积需要乘以步长 dt 来模拟积分面积
g1 = conv(f1, f1) * dt;
g2 = conv(f2, f2) * dt;
g3 = conv(f1, f2) * dt;

% 4. 定义卷积结果的时间轴
% 卷积后的时间起点 = 信号1起点 + 信号2起点
% 卷积后的长度 = length(f1) + length(f2) - 1
t_g1 = linspace(t(1)+t(1), t(end)+t(end), length(g1));
t_g2 = linspace(t(1)+t(1), t(end)+t(end), length(g2));
t_g3 = linspace(t(1)+t(1), t(end)+t(end), length(g3));

% 5. 绘图
figure('Name', '第1题: 信号卷积');

% 绘制 g1 = f1 * f1
subplot(3,2,1); plot(t, f1, 'LineWidth', 1.5); title('f_1(t)'); grid on; ylim([-0.5 1.5]);
subplot(3,2,2); plot(t_g1, g1, 'r', 'LineWidth', 1.5); title('g_1(t) = f_1 * f_1'); grid on;

% 绘制 g2 = f2 * f2
subplot(3,2,3); plot(t, f2, 'LineWidth', 1.5); title('f_2(t)'); grid on; ylim([-0.5 1.5]);
subplot(3,2,4); plot(t_g2, g2, 'r', 'LineWidth', 1.5); title('g_2(t) = f_2 * f_2'); grid on;

% 绘制 g3 = f1 * f2
subplot(3,2,5); plot(t, f1, 'b', t, f2, '--k', 'LineWidth', 1.5); title('f_1(t) & f_2(t)'); grid on; legend('f1','f2');
subplot(3,2,6); plot(t_g3, g3, 'r', 'LineWidth', 1.5); title('g_3(t) = f_1 * f_2'); grid on;
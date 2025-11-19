% 第2题 MATLAB代码
clc; clear; close all;

% 1. 定义时间参数
dt = 0.001;
t = -1:dt:6; % 适当扩大范围以容纳卷积结果

% 2. 定义信号
% f1(t): 0到2之间为1
f1 = 1 * ((t >= 0) & (t < 2));

% f2(t): 分段函数
% 0-1为1, 1-2为2, 2-3为1
f2 = 1 * ((t >= 0) & (t < 1)) + ...
     2 * ((t >= 1) & (t < 2)) + ...
     1 * ((t >= 2) & (t < 3));

% 3. 计算卷积
g = conv(f1, f2) * dt;

% 4. 定义卷积结果的时间轴
t_g = linspace(t(1)+t(1), t(end)+t(end), length(g));

% 5. 绘图
figure('Name', '第2题: 矩形与阶梯信号卷积');

subplot(3,1,1);
plot(t, f1, 'LineWidth', 2);
title('f_1(t)'); axis([-1 5 -0.5 1.5]); grid on;

subplot(3,1,2);
plot(t, f2, 'LineWidth', 2);
title('f_2(t)'); axis([-1 5 -0.5 2.5]); grid on;

subplot(3,1,3);
plot(t_g, g, 'r', 'LineWidth', 2);
title('卷积结果 f_1(t) * f_2(t)'); 
xlim([-1 6]); grid on;
xlabel('时间 t');
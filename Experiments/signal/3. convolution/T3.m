% 第3题 MATLAB代码
clc; clear; close all;

% 1. 定义时间参数
dt = 0.001;
t = -4:dt:4; 

% 2. 定义信号
% f1(t): -1到1之间为1
f1 = 1 * ((t >= -1) & (t < 1));

% f2(t): 梯形信号
% 区间 [-3, -2]: 线性上升 y = t + 3
% 区间 [-2, 0]: 恒定为 1
% 区间 [0, 1]: 线性下降 y = -t + 1
f2 = zeros(size(t));
f2((t >= -3) & (t < -2)) = t((t >= -3) & (t < -2)) + 3;
f2((t >= -2) & (t < 0))  = 1;
f2((t >= 0) & (t < 1))   = -t((t >= 0) & (t < 1)) + 1;

% 3. 计算卷积
g = conv(f1, f2) * dt;

% 4. 卷积结果的时间轴
t_g = linspace(t(1)+t(1), t(end)+t(end), length(g));

% 5. 绘图
figure('Name', '第3题: 矩形与梯形信号卷积');

subplot(3,1,1);
plot(t, f1, 'LineWidth', 2);
title('f_1(t)'); axis([-4 4 -0.2 1.2]); grid on;

subplot(3,1,2);
plot(t, f2, 'LineWidth', 2);
title('f_2(t)'); axis([-4 4 -0.2 1.2]); grid on;

subplot(3,1,3);
plot(t_g, g, 'r', 'LineWidth', 2);
title('卷积结果 f_1(t) * f_2(t)'); 
xlim([-5 5]); grid on;
xlabel('时间 t');z
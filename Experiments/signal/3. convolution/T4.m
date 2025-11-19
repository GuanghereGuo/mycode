% 第4题 MATLAB代码
clc; clear; close all;

% 1. 定义时间参数
dt = 0.01;
t = -3:dt:8; % 选取足够宽的时间窗口

% 2. 定义信号
% f1(t) = (t-1)[u(t-1) - u(t-3)]
% 在 1到3 之间是斜坡 (t-1)，其他为0
f1 = (t - 1) .* ((t >= 1) & (t < 3));

% f2(t) = u(t+1) - 2u(t-2)
% t < -1: 0
% -1 <= t < 2: 1
% t >= 2: 1 - 2 = -1
f2 = 1.0 * (t >= -1) - 2.0 * (t >= 2);

% 3. 计算卷积
g = conv(f1, f2) * dt;

% 4. 卷积结果的时间轴
t_g = linspace(t(1)+t(1), t(end)+t(end), length(g));

% 5. 绘图
figure('Name', '第4题: 斜坡与阶跃组合卷积');

subplot(3,1,1);
plot(t, f1, 'LineWidth', 2);
title('f_1(t) = (t-1)[u(t-1)-u(t-3)]'); 
grid on; xlim([-2 6]);

subplot(3,1,2);
plot(t, f2, 'LineWidth', 2);
title('f_2(t) = u(t+1) - 2u(t-2)'); 
grid on; xlim([-2 6]); ylim([-1.5 1.5]);

subplot(3,1,3);
plot(t_g, g, 'r', 'LineWidth', 2);
title('卷积结果 g(t)');
grid on; xlim([-2 8]); % 限制显示范围以观察主要变化
xlabel('时间 t');
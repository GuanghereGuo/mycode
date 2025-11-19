clc; clear; close all;

% 1. 定义时间轴和步长
dt = 0.01;             % 采样步长，越小越精确
t_min = -2;            % 定义信号的观测范围
t_max = 8;             
t = t_min:dt:t_max;    % 时间向量

% 2. 定义阶跃函数句柄 (方便写表达式)
u = @(x) (x >= 0) * 1.0; 

% 3. 构造两个信号
% f1(t) = (t-1)[u(t-1) - u(t-3)]
f1 = (t - 1) .* (u(t - 1) - u(t - 3));

% f2(t) = 2u(t+1) - 3u(t-2)
f2 = 2 * u(t + 1) - 3 * u(t - 2);

% 4. 计算卷积
% 注意：数值卷积的结果需要乘以 dt 才是近似的积分值
g = conv(f1, f2) * dt; 

% 5. 调整卷积后的时间轴
% 卷积后的起始时间 = 两个信号起始时间之和
% 长度 = length(f1) + length(f2) - 1
t_start_g = t(1) + t(1); 
tg = t_start_g + (0:length(g)-1) * dt;

% 6. 绘图
figure; 

% 绘制 f1
subplot(3,1,1);
plot(t, f1, 'LineWidth', 2);
grid on; ylim([-0.5, 2.5]); title('f_1(t)');
ylabel('幅度');

% 绘制 f2
subplot(3,1,2);
plot(t, f2, 'LineWidth', 2);
grid on; ylim([-1.5, 2.5]); title('f_2(t)');
ylabel('幅度');

% 绘制卷积结果 g(t)
subplot(3,1,3);
plot(tg, g, 'LineWidth', 2);
grid on; 
xlim([-1, 8]); % 限制一下显示范围，方便观察
title('卷积结果 g(t) = f_1(t) * f_2(t)');
xlabel('时间 t'); ylabel('幅度');

% 标记一下最终稳定值
yline(-2, '--k', 'Final Value -2');
% 题目 2：信号的变换
% 清理工作区
clear; clc; close all;

% 1. 根据图像定义原始信号 f(t)
% 使用匿名函数和逻辑索引
% f(t) = 2, 0 <= t < 1
% f(t) = 1, 1 <= t < 2
% f(t) = 0, 其它
f = @(t) 2 * (t >= 0 & t < 1) + 1 * (t >= 1 & t < 2);

% 2. 定义一个足够宽的时间范围用于绘图
t = linspace(-4, 6, 2000); % 使用高密度点以保证阶跃边缘清晰

% 3. 创建新图形窗口
figure;
sgtitle('题目 2 信号变换');
common_ylim = [-0.5, 2.5]; % 统一y轴范围

% (1) f(-t) [时间反转]
subplot(3, 2, 1);
plot(t, f(-t), 'LineWidth', 1.5);
title('(1) f(-t)');
xlabel('t');
ylabel('f(-t)');
grid on;
ylim(common_ylim);

% (2) f(t - 2) [时间平移]
subplot(3, 2, 2);
plot(t, f(t - 2), 'LineWidth', 1.5);
title('(2) f(t - 2)');
xlabel('t');
ylabel('f(t-2)');
grid on;
ylim(common_ylim);

% (3) f(at) 其中 a = 0.5 [时间尺度变换 - 扩展]
subplot(3, 2, 3);
plot(t, f(0.5 * t), 'LineWidth', 1.5);
title('(3) f(0.5t) (a=0.5, 扩展)');
xlabel('t');
ylabel('f(0.5t)');
grid on;
ylim(common_ylim);

% (3) f(at) 其中 a = 2 [时间尺度变换 - 压缩]
subplot(3, 2, 4);
plot(t, f(2 * t), 'LineWidth', 1.5);
title('(3) f(2t) (a=2, 压缩)');
xlabel('t');
ylabel('f(2t)');
grid on;
ylim(common_ylim);

% (4) f(0.5t + 1) [复合变换]
subplot(3, 2, 5);
plot(t, f(0.5 * t + 1), 'LineWidth', 1.5);
title('(4) f(0.5t + 1)');
xlabel('t');
ylabel('f(0.5t+1)');
grid on;
ylim(common_ylim);

% 额外: 绘制原始信号 f(t) 以供对比
subplot(3, 2, 6);
plot(t, f(t), 'LineWidth', 1.5, 'Color', 'k'); % 黑色
title('原始信号 f(t)');
xlabel('t');
ylabel('f(t)');
grid on;
ylim(common_ylim);
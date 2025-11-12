% 题目 1：使用数值运算
% 清理工作区
clear; clc; close all;

% 创建一个新图形窗口
figure;
sgtitle('题目 1'); % Super title (总标题)

% (1) f(t) = (2 - e^(-2t))u(t)
subplot(2, 2, 1);
t1 = linspace(0, 5, 500); % u(t) 表示 t >= 0
f1 = (2 - exp(-2*t1));
plot(t1, f1, 'LineWidth', 1.5);
title('(1) f(t) = (2 - e^{-2t})u(t)');
xlabel('t');
ylabel('f(t)');
grid on;

% (2) f(t) = cos(pi*t/2)[u(t) - u(t - 4)]
subplot(2, 2, 2);
t2 = linspace(-1, 5, 600); % 信号在 [0, 4] 之外为 0
% 定义矩形窗 [u(t) - u(t - 4)]
window = (t2 >= 0) - (t2 >= 4);
f2 = cos(pi*t2/2) .* window;
plot(t2, f2, 'LineWidth', 1.5);
title('(2) f(t) = cos(\pi t/2)[u(t) - u(t - 4)]');
xlabel('t');
ylabel('f(t)');
grid on;

% (3) f(t) = e^t * cos(t) * u(t)
subplot(2, 2, 3);
t3 = linspace(0, 3, 500); % u(t) 表示 t >= 0，此函数增长很快
f3 = exp(t3) .* cos(t3);
plot(t3, f3, 'LineWidth', 1.5);
title('(3) f(t) = e^t cos(t)u(t)');
xlabel('t');
ylabel('f(t)');
grid on;

% (4) f(t) = (2/3)t * u(t + 2)
subplot(2, 2, 4);
t4 = linspace(-2, 4, 500); % u(t + 2) 表示 t >= -2
f4 = (2/3) * t4;
plot(t4, f4, 'LineWidth', 1.5);
title('(4) f(t) = (2/3)tu(t + 2)');
xlabel('t');
ylabel('f(t)');
grid on;
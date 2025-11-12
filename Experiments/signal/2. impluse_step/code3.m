% 题目 3：复信号的实部、虚部、模和辅角
% 清理工作区
clear; clc; close all;

% 定义时间向量，绘制几个周期
t = linspace(-2*pi, 2*pi, 500);

% 定义复信号 f(t)
% 注意：在 Matlab 中， j (或 i) 用 1i 表示
f = 2 * exp(1i * (t + pi/4));

% 创建新图形窗口
figure;
sgtitle('题目 3 复信号 f(t) = 2e^{j(t+\pi/4)}');

% (1) 绘制实部
subplot(2, 2, 1);
plot(t, real(f), 'LineWidth', 1.5);
title('实部');
xlabel('t');
ylabel('Re\{f(t)\}');
grid on;

% (2) 绘制虚部
subplot(2, 2, 2);
plot(t, imag(f), 'LineWidth', 1.5);
title('虚部');
xlabel('t');
ylabel('Im\{f(t)\}');
grid on;

% (3) 绘制模 (幅度)
subplot(2, 2, 3);
plot(t, abs(f), 'LineWidth', 1.5);
title('模');
xlabel('t');
ylabel('|f(t)|');
ylim([0, 3]); % 设置y轴范围，使其更清晰
grid on;

% (4) 绘制辅角 (相位)
% angle(f) 会将相位卷绕(wrap)在 [-pi, pi] 之间
% unwrap(angle(f)) 可以显示连续的相位
subplot(2, 2, 4);
plot(t, unwrap(angle(f)), 'LineWidth', 1.5);
title('幅角');
xlabel('t');
ylabel('\anglef(t)');
grid on;
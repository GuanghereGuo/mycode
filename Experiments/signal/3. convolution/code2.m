clear; close all; clc;

delta = 0.01;
t = -2:delta:2;

f1 = heaviside(t) - heaviside(t-1);    % f1(t)=u(t)-u(t-1)
f2 = heaviside(t+1) - heaviside(t);    % f2(t)=u(t+1)-u(t)

y = conv(f1, f2) * delta;
n = length(y);
t_start = t(1) + t(1);               % 卷积起始时刻 = f1_start + f2_start
t_y = (0:n-1) * delta + t_start;     % 对应 time axis for y

figure('Name','f1, f2 and convolution','Position',[100 100 900 450]);
subplot(3,1,1)
plot(t, f1, 'LineWidth', 1.6); grid on;
axis([min(t) max(t) -0.1 1.1]); title('f_1(t)=u(t)-u(t-1)');
xlabel('t');

subplot(3,1,2)
plot(t, f2, 'LineWidth', 1.6); grid on;
axis([min(t) max(t) -0.1 1.1]); title('f_2(t)=u(t+1)-u(t)');
xlabel('t');

subplot(3,1,3)
plot(t_y, y, 'LineWidth', 1.6); grid on;
axis([min(t_y) max(t_y) -0.05 max(y)+0.1]); title('y(t)=f_1 * f_2');
xlabel('t');

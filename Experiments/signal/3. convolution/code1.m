clear all; clc;

delta = 0.01;

t = 0:delta:15;

f = exp(-t);

h = (t.^2).*exp(-2*t);

y = conv(f, h) * delta;

n = length(y);
t_y = (0:n-1) * delta;
plot(t_y, y, 'LineWidth', 1.5);
xlabel('t');
ylabel('y(t) = f(t) * h(t)');
title('卷积数值结果');
grid on;
axis([0 15 -0.01 0.1]);

t = -2:0.001:2;

w = -26*pi : 0.05 : 26*pi; 
w_calc = w + eps;

f_t = 4 * (heaviside(t + 0.25) - heaviside(t - 0.25));
f_t(abs(t)==0.25) = 2;

carrier = cos(12 * pi * t);

f_mod = f_t .* carrier;

F_w = 4 * 0.5 * sin(w_calc * 0.5 / 2) ./ (w_calc * 0.5 / 2);
F_mag = abs(F_w);

w0 = 12 * pi;
F_w_left = 4 * 0.5 * sin((w_calc+w0) * 0.5 / 2) ./ ((w_calc+w0) * 0.5 / 2);
F_w_right = 4 * 0.5 * sin((w_calc-w0) * 0.5 / 2) ./ ((w_calc-w0) * 0.5 / 2);

F_mod_mag = abs(0.5 * F_w_left + 0.5 * F_w_right);

figure('Color', 'w', 'Position', [100, 100, 1200, 700]);

subplot(3, 2, 1);
plot(t, f_t, 'b', 'LineWidth', 1);
grid on; axis([-2 2 -0.5 4.5]);
title('原始信号 f(t)'); 

subplot(3, 2, 3);
plot(t, carrier, 'b', 'LineWidth', 0.5);
grid on; axis([-2 2 -1.2 1.2]);
title('调制信号');

subplot(3, 2, 5);
plot(t, f_mod, 'b', 'LineWidth', 1);
grid on; axis([-2 2 -4.5 4.5]);
title('调制后信号');


ticks_pi = -24:4:24;
tick_locs = ticks_pi * pi;
tick_labels = arrayfun(@(n) sprintf('%d*pi', n), ticks_pi, 'UniformOutput', false);
tick_labels{ticks_pi==0} = '0';


subplot(2, 2, 2); 
plot(w, F_mag, 'LineWidth', 1);
grid on; axis([-26*pi 26*pi 0 2.2]);
title('矩形信号频谱');
set(gca, 'XTick', tick_locs, 'XTickLabel', tick_labels, 'FontSize', 8);

subplot(2, 2, 4);
plot(w, F_mod_mag, 'LineWidth', 1); hold on;

xline(-12*pi, 'r', 'LineWidth', 1.5);
xline(12*pi, 'r', 'LineWidth', 1.5);
grid on; axis([-26*pi 26*pi 0 1.2]);
title('矩形调制信号频谱');
set(gca, 'XTick', tick_locs, 'XTickLabel', tick_labels, 'FontSize', 8);
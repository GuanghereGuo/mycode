t = -1.5:0.001:1.5;
w = -30:0.1:30;
w_calc = w;
w_calc(w_calc==0) = eps; 

y1 = heaviside(t + 0.5) - heaviside(t - 0.5);
y1(abs(t)==0.5) = 1; 

Y1 = (2 * abs(sin(0.5 * w_calc))) ./ abs(w_calc);

y2 = heaviside(t + 1.0) - heaviside(t - 1.0);
y2(abs(t)==1.0) = 1;

Y2 = (2 * abs(sin(1.0 * w_calc))) ./ abs(w_calc);

y3 = heaviside(t + 0.25) - heaviside(t - 0.25);
y3(abs(t)==0.25) = 1;

Y3 = (2 * abs(sin(0.25 * w_calc))) ./ abs(w_calc);

figure('Color', 'w', 'Position', [100, 100, 1000, 600]);

% Row 1
subplot(3, 2, 1);
plot(t, y1, 'LineWidth', 1.5);
axis([-1.5 1.5 0 1.2]); grid on;
title('heaviside(t + 0.5) - heaviside(t - 0.5)');
xlabel('t');

subplot(3, 2, 2);
plot(w, Y1, 'LineWidth', 1.5);
axis([-30 30 0 2.2]); grid on;
title('(2 abs(sin(0.5 w)))/abs(w)');
xlabel('w');

% Row 2 
subplot(3, 2, 3);
plot(t, y2, 'LineWidth', 1.5);
axis([-1.5 1.5 0 1.2]); grid on;
title('heaviside(t + 1.0) - heaviside(t - 1.0)');
xlabel('t');

subplot(3, 2, 4);
plot(w, Y2, 'LineWidth', 1.5);
axis([-30 30 0 2.2]); grid on;
title('(2 abs(sin(1.0 w)))/abs(w)');
xlabel('w');

% Row 3
subplot(3, 2, 5);
plot(t, y3, 'LineWidth', 1.5);
axis([-1.5 1.5 0 1.2]); grid on;
title('heaviside(t + 0.25) - heaviside(t - 0.25)');
xlabel('t');

subplot(3, 2, 6);
plot(w, Y3, 'LineWidth', 1.5);
axis([-30 30 0 2.2]); grid on;
title('(2 abs(sin(0.25 w)))/abs(w)');
xlabel('w');
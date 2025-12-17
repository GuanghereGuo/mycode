[x, fs] = audioread('../test1.wav');
if size(x, 2) > 1; x = x(:, 1); end

t = (0:length(x)-1)'/fs;
noise =  0.3 * sin(2*pi*1800*t);
x_noisy = x + noise;

f0 = 1800;
w0 = 2*pi*f0/fs;
r = 0.99;

b = [1, -2*cos(w0), 1];
a = [1, -2*r*cos(w0), r^2];
k = sum(a) / sum(b);
b = b * k;

y_clean = filter(b, a, x_noisy);
% y_clean(1:10000) = 0;

disp(length(x_noisy));

audiowrite('task1_noisy.wav', x_noisy, fs);
audiowrite('task1_filtered.wav', y_clean, fs);
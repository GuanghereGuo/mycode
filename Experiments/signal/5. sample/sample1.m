t = -5 : 0.01 : 5;  
ft = sin(t) ./ t;

Ts_val = 0.5; 

Ts_axis = -5 : Ts_val : 5;  
fs_samples = sin(Ts_axis) ./ Ts_axis; 
fs_samples(isnan(fs_samples)) = 1;

w = -40 : 0.01 : 40;

% Fsw = Ts_val * fs_samples * exp(-1j * Ts_axis' * w);
Fsw = fs_samples * exp(-1j * Ts_axis' * w);

param_matrix = (ones(length(Ts_axis),1)*t - Ts_axis'*ones(1,length(t))) / Ts_val;
g = fs_samples * sinc(param_matrix);
e = abs(ft - g);

figure('Name', '采样定理与信号重建', 'Color', 'w', 'Position', [100, 100, 1000, 700]);

subplot(2,2,1);
stem(Ts_axis, fs_samples, 'Filled', 'LineWidth', 1);
title('1. 抽样信号 f_s(t) (时域)');
xlabel('t'); grid on;

subplot(2,2,2);
plot(w, abs(Fsw), 'b', 'LineWidth', 1);
title('2. 抽样信号频谱 |F_s(\omega)|');
xlabel('\omega'); grid on;
xlim([-30 30]);

subplot(2,2,3);
plot(t, ft, 'b', 'LineWidth', 1.5); hold on;
plot(t, g, 'r--', 'LineWidth', 1.5);
legend('原信号', '重建信号');
title('3. 信号重建对比');
xlabel('t'); grid on;

subplot(2,2,4);
plot(t, e, 'k', 'LineWidth', 1);
title(['4. 重建误差 (采样间隔 Ts = ' num2str(Ts_val) ')']);
xlabel('t'); grid on;
if max(e) < 1e-10
    ylim([0, 1e-10]);
end
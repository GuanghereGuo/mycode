N = length(x_noisy);
f = (0:N-1)*(fs/N);
X_noisy_db = 20*log10(abs(fft(x_noisy))/N + eps);
Y_clean_db = 20*log10(abs(fft(y_clean))/N + eps);

figure('Color', 'w');
subplot(2, 1, 1);
plot(f, X_noisy_db);
xlim([1600, 2000]); 
ylim([-120, 0]);
grid on;
title('Noisy Spectrum (dB)');
ylabel('Magnitude (dB)');

subplot(2, 1, 2);
plot(f, Y_clean_db);
xlim([1600, 2000]); 
ylim([-120, 0]);
grid on;
title('Filtered Spectrum (dB)');
ylabel('Magnitude (dB)');
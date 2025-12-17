figure('Color', 'w');
zplane(b, a);
title('');

figure('Color', 'w');
[H, F] = freqz(b, a, 4096, fs);
plot(F, 20*log10(abs(H)), 'LineWidth', 1.5);
grid on;
xlim([0, fs/2]);
xlabel('Frequency (Hz)');
ylabel('Magnitude (dB)');
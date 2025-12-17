[x_orig, fs] = audioread('../test2.wav');
if size(x_orig, 2) > 1; x_orig = x_orig(:, 1); end
y_reverse = flipud(x_orig);

win = 2048;
noverlap = 1024;
nfft = 2048;

[~, F_orig, T_orig, P_orig] = spectrogram(x_orig, win, noverlap, nfft, fs);
P_orig_db = 10*log10(P_orig + eps);

[~, F_rev, T_rev, P_rev] = spectrogram(y_reverse, win, noverlap, nfft, fs);
P_rev_db = 10*log10(P_rev + eps);

figure('Color', 'w', 'Position', [100, 100, 1200, 500]);

subplot(1, 2, 1);
surf(T_orig, F_orig, P_orig_db);
shading interp;
axis tight;
view(-30, 45);
colormap jet;
ylim([0, 5000]);
xlabel('Time (s)');
ylabel('Frequency (Hz)');
zlabel('Power (dB)');
title('Original 3D Spectrogram');

subplot(1, 2, 2);
surf(T_rev, F_rev, P_rev_db);
shading interp;
axis tight;
view(-30, 45);
colormap jet;
ylim([0, 5000]);
xlabel('Time (s)');
ylabel('Frequency (Hz)');
zlabel('Power (dB)');
title('Reversed 3D Spectrogram');
filename = 'test0.wav';

try
    [y, fs] = audioread(filename);
catch
    error('未找到音频文件');
end

N = length(y);

disp('正在播放原始音频 f(t)');
sound(y, fs);
pause(N/fs + 1);

disp('正在处理并播放 f(2t)');
sound(y, 2 * fs);
pause(N/(2*fs) + 1);

disp('正在处理并播放 f(t/2)');
sound(y, fs / 2);
% pause(N/(fs/2) + 1);
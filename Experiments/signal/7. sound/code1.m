filename = 'test0.wav';

try
    [y, fs] = audioread(filename);
catch
    error('未找到音频文件');
end

% 获取时间轴
N = length(y);
t = (0:N-1) / fs;

disp('正在播放原始音频 f(t)');
sound(y, fs);

pause(N/fs + 1); 

disp('正在处理并播放 f(2t)');

y_fast = resample(y, 1, 2); 

sound(y_fast, fs);
pause(length(y_fast)/fs + 1);

disp('正在处理并播放 f(t/2)');

y_slow = resample(y, 2, 1);

sound(y_slow, fs);
pause(length(y_slow)/fs + 1);

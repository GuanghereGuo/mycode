filename = 'test3.wav';

try
    [y, fs] = audioread(filename);
catch
    error('未找到音频文件');
end

N = length(y);

disp('正在播放原始音频 f(t)');
sound(y, fs);
pause(N/fs + 1);

disp('正在播放倒放音频 f(-t)');

y_reverse = flipud(y);

sound(y_reverse, fs);
pause(N/fs + 1);

audiowrite('test_reverse.wav', y_reverse, fs);
disp('文件已保存');
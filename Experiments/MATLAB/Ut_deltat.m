% t = -4:0.01:4;
% ut = stepfun(t, 0);
% plot(t, ut);
% axis([-1, 4, -0.5, 1.5])

% gt = stepfun(t, -2) - stepfun(t, 2);
% plot(t, gt)
% axis([-4, 4, -0.5, 1.5])

% t = -5:0.01:5;
% s = sign(t);
% u = 0.5 + 0.5 * s
% subplot(2, 1, 1);
% plot(t, s);title('符号函数');
% axis([-5, 5, -1.5, 1.5]);
% subplot(2,1,2);
% plot(t, u);title('单位阶跃函数');
% axis([-5, 5, -0.5, 1.5]);

% t = 0:0.01:2*pi;
% f = sin(t);
% plot(t, f);
% title('sin(x)')

% t = 0:0.01:5;
% f = exp(t);
% plot(t, f);
% title("exp(x)");



% t = -2*pi:0.01:2*pi;
% f = sinc(t);
% plot(t, f);
% title('sinc(x)')


% t = -10:0.01:10;    
% w = 4;              
% y = tripuls(t, w); 
% 
% plot(t, y, 'LineWidth', 1.5);
% xlabel('t');
% ylabel('Amplitude');
% title(['三角脉冲信号']);

% t = -10:0.01:10;    
% w = 10;              
% y = tripuls(t, w); 
% 
% plot(t, y, 'LineWidth', 1.5);
% xlabel('t');
% ylabel('Amplitude');
% title(['三角脉冲信号']);


% t = -15:0.01:15;   
% width = 0.5;     
% y = sawtooth(t, width);
% 
% plot(t, y, 'LineWidth', 1.5);
% xlabel('t');
% ylabel('Amplitude');
% title(['三角波周期信号 w=0.5']);

% t = -15:0.01:15;   
% width = 1;     
% y = sawtooth(t, width);
% 
% plot(t, y, 'LineWidth', 1.5);
% xlabel('t');
% ylabel('Amplitude');
% title(['三角波周期信号 w=1']);

% t = -15:0.01:15;   
% width = 0;     
% y = sawtooth(t, width);
% 
% plot(t, y, 'LineWidth', 1.5);
% xlabel('t');
% ylabel('Amplitude');
% title(['三角波周期信号 w=0']);

% t = -10:0.01:10;   
% w = 2;              
% y = rectpuls(t, w);
% 
% plot(t, y, 'LineWidth', 1.5);
% xlabel('t');
% ylabel('Amplitude');
% title(['矩形脉冲信号']);

% t = -15:0.01:15;   
% duty = 50;           
% y = square(t, duty);
% 
% plot(t, y, 'LineWidth', 1.5);
% xlabel('t');
% ylabel('Amplitude');
% title(['周期矩形波信号']);


% t = -4:0.01:4;
% f = (t>=0 & t<1)*2 + (t>=1 & t<2)*1;
% 
% 
% t_new = -10:0.01:10;
% tt = 0.3*t_new + 1;
% 
% f_new = (tt>=0 & tt<1)*2 + (tt>=1 & tt<2)*1;
% 
% subplot(2,1,1);
% plot(t, f, 'LineWidth', 1.5);
% xlabel('t'); ylabel('f(t)');
% title('原信号 f(t)');
% grid on;
% 
% subplot(2,1,2);
% plot(t_new, f_new, 'r', 'LineWidth', 1.5);
% xlabel('t'); ylabel('f(0.3t + 1)');
% title('变换后信号 f(0.3t + 1)');
% grid on;

% 文件名: multi_wave_subplot.m
clc; clear; close all;

t = -15:0.01:15;  % 时间轴

% ===== 三角周期波 =====
y1 = sawtooth(t, 0.5);   % 对称三角波
y2 = sawtooth(t, 0.2);   % 不对称三角波

% ===== 矩形周期波 =====
y3 = square(t, 50);  % 占空比 50%
y4 = square(t, 20);  % 占空比 20%
y5 = square(t, 80);  % 占空比 80%

% ===== 绘图 =====
figure;

subplot(5,1,1);
plot(t, y1, 'LineWidth', 1.5);
title('三角周期波 sawtooth(t, 0.5)');
xlabel('t'); ylabel('Amplitude');
grid on;

subplot(5,1,2);
plot(t, y2, 'LineWidth', 1.5);
title('三角周期波 sawtooth(t, 0.2)');
xlabel('t'); ylabel('Amplitude');
grid on;

subplot(5,1,3);
plot(t, y3, 'LineWidth', 1.5);
title('矩形波 square(t, 50)');
xlabel('t'); ylabel('Amplitude');
grid on;

subplot(5,1,4);
plot(t, y4, 'LineWidth', 1.5);
title('矩形波 square(t, 20)');
xlabel('t'); ylabel('Amplitude');
grid on;

subplot(5,1,5);
plot(t, y5, 'LineWidth', 1.5);
title('矩形波 square(t, 80)');
xlabel('t'); ylabel('Amplitude');
grid on;

% 优化整体布局
sgtitle('两个三角周期波与三个矩形周期波');

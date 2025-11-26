%% 1. 数据录入区域 (请将实验数据填入下方的方括号中)
% ===========================================================

% --- 表 4-1 (a) 低通无源滤波器数据 ---
% 输入频率 f (Hz)
f_passive = [100, 1e3, 5e3, 10e3, 15e3,18.5e3, 20e3, 25e3, 30e3, 50e3, 100e3]; 
% 输入输出电压 Vo (V)
Vo_passive = [3.84, 3.84, 3.84, 3.44, 3.04, 2.8, 2.72, 2.40, 2.08, 1.36, 0.72]; 

% --- 表 4-1 (b) 低通有源滤波器数据 ---
% 输入频率 f (Hz)
f_active = [100, 1e3, 5e3, 10e3, 16.7e3, 17e3, 20e3, 25e3, 30e3, 50e3, 100e3];  
% 输入输出电压 Vo (V)
Vo_active = [3.84, 3.84, 3.84, 3.68, 2.8, 2.72, 2.24, 1.60, 1.28, 0.56, 0.24];

% ===========================================================


%% 2. 绘图逻辑 (无需修改)

% 创建图形窗口
figure('Name', '低通滤波器频率特性曲线', 'Color', 'w');

% --- 绘图 1: 无源滤波器 ---
subplot(1, 2, 1); % 2行1列，第1张图
plot_filter_response(f_passive, Vo_passive, '低通无源滤波器幅频特性');

% --- 绘图 2: 有源滤波器 ---
subplot(1, 2, 2); % 2行1列，第2张图
plot_filter_response(f_active, Vo_active, '低通有源滤波器幅频特性');


%% 3. 辅助函数：用于拟合和绘图
function plot_filter_response(f, Vo, title_str)
    % 生成平滑的拟合曲线数据
    % 使用对数间距生成更密集的频率点，以便在对数坐标下曲线平滑
    f_fit = logspace(log10(min(f)), log10(max(f)), 500); 
    
    % 使用样条插值 (spline) 进行拟合
    Vo_fit = interp1(f, Vo, f_fit, 'spline'); 
    
    % 绘制实验数据点 (圆圈)
    semilogx(f, Vo, 'ro', 'MarkerFaceColor', 'r', 'DisplayName', '实验测量点');
    hold on;
    
    % 绘制拟合曲线 (蓝线)
    semilogx(f_fit, Vo_fit, 'b-', 'LineWidth', 1.5, 'DisplayName', '拟合曲线');
    
    % 寻找最大电压并绘制 0.707 参考线 (截止频率位置)
    max_V = max(Vo);
    cutoff_V = max_V * 0.707;
    yline(cutoff_V, 'k--', 'LineWidth', 1, 'DisplayName', '-3dB (0.707Vm)');
    
    % 图表美化
    grid on; % 打开网格
    xlabel('频率 f (Hz)');
    ylabel('输出电压 V_o (V)');
    title(title_str);
    legend('Location', 'southwest'); % 图例位置
    axis tight; % 坐标轴紧凑
    
    % 设置X轴刻度显示更友好
    xticks([10, 100, 1000, 10000, 100000, 1000000]);
    xticklabels({'10', '100', '1k', '10k', '100k', '1M'});
    
    hold off;
end

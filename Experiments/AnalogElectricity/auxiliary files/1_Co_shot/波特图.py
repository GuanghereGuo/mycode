import numpy as np
import matplotlib.pyplot as plt

# --- 1. 设置中文字体 (用于正确显示标签) ---
# 解决matplotlib显示中文时乱码的问题
# 你可能需要根据你的系统安装/指定一个中文字体，例如 'SimHei', 'Microsoft YaHei' 等
plt.rcParams['font.sans-serif'] = ['SimHei']  # 指定默认字体
plt.rcParams['axes.unicode_minus'] = False  # 解决保存图像是负号'-'显示为方块的问题

# --- 2. 定义已知常量 ---
Vin_pp = 100.0       # mV
Vopp_mid = 466.58    # mV
fL = 25.0            # Hz (低频截止频率)
fH = 1.8e6           # Hz (高频截止频率, 1.8 MHz)

# --- 3. 计算关键增益值 ---
# 中频线性增益
Av_mid = Vopp_mid / Vin_pp
# 中频dB增益
Av_mid_db = 20 * np.log10(Av_mid)
# -3dB 增益
Av_3db = Av_mid_db - 3.0

print(f"中频增益 (Av,mid): {Av_mid:.4f}")
print(f"中频增益 (dB): {Av_mid_db:.2f} dB")
print(f"-3dB 截止点增益: {Av_3db:.2f} dB")

# --- 4. 创建频率范围 ---
# 创建一个从 1 Hz 到 10 MHz 的对数间隔频率点
# np.logspace(0, 7) 表示 10^0 到 10^7
frequencies = np.logspace(0, 7, 1000)  # 1 Hz to 10 MHz

# --- 5. 计算传递函数（增益幅度） ---
# 使用标准单极点高通和单极点低通模型
# 低通部分: 1 / sqrt(1 + (f/fH)^2)
low_pass = 1.0 / np.sqrt(1 + (frequencies / fH)**2)
# 高通部分: (f/fL) / sqrt(1 + (f/fL)^2)
high_pass = (frequencies / fL) / np.sqrt(1 + (frequencies / fL)**2)

# 总的线性增益幅度
Av_mag = Av_mid * high_pass * low_pass

# 转换为 dB
Av_mag_db = 20 * np.log10(Av_mag)

# --- 6. 绘图 ---
plt.figure(figsize=(12, 7))
# 绘制幅频特性曲线
plt.semilogx(frequencies, Av_mag_db, label='放大器增益 (A_v)', color='blue', linewidth=2)

# 标记中频增益
plt.axhline(y=Av_mid_db, color='green', linestyle='--', label=f'中频增益 ({Av_mid_db:.2f} dB)')
# 标记-3dB增益
plt.axhline(y=Av_3db, color='red', linestyle='--', label=f'-3dB 增益 ({Av_3db:.2f} dB)')

# 标记截止频率
plt.axvline(x=fL, color='orange', linestyle=':', label=f'fL = {fL} Hz')
plt.axvline(x=fH, color='purple', linestyle=':', label=f'fH = {fH/1e6} MHz')

# --- 7. 设置图表样式 ---
plt.title('幅频特性', fontsize=16)
plt.xlabel('频率 (Hz)', fontsize=12)
plt.ylabel('增益 (dB)', fontsize=12)
plt.grid(True, which="both", linestyle='-', linewidth=0.5, alpha=0.7)
plt.legend()
plt.show()
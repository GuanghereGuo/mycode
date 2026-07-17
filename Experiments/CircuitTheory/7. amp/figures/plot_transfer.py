"""反向比例放大器输入输出传输特性绘图。

数据为实测峰峰值，1 kHz 正弦输入。输出在约 8.01 V 处饱和。
图内标签使用英文，避免系统缺少中文字体导致的渲染问题。
"""

import numpy as np
import matplotlib

matplotlib.use("Agg")
import matplotlib.pyplot as plt

Vi = np.array([0.14, 0.24, 0.32, 0.51, 0.70, 0.98, 1.18, 1.38, 1.78, 1.98])
Vo = np.array([0.85, 1.62, 2.31, 3.93, 5.46, 7.71, 8.01, 8.01, 8.01, 8.01])

V_sat = 8.01

# 用全部未饱和点做拟合
fit_mask = Vo < 8.0
slope, intercept = np.polyfit(Vi[fit_mask], Vo[fit_mask], 1)
print(f"linear fit (unsaturated): slope={slope:.3f}, intercept={intercept:.3f}")

# 各点实测增益
for vi, vo in zip(Vi, Vo):
    print(f"  Vi={vi:.2f}  Vo={vo:.2f}  Vo/Vi={vo/vi:.2f}")

# 饱和起始输入估计：拟合直线与饱和电平交点
vi_sat = (V_sat - intercept) / slope
print(f"saturation onset Vi ~ {vi_sat:.2f} V")

fig, ax = plt.subplots(figsize=(6.2, 4.3))

x_ideal = np.linspace(0, 0.85, 50)
ax.plot(x_ideal, 10 * x_ideal, "--", color="0.5", label=r"Ideal gain $|A_v|=10$")

x_fit = np.linspace(0, 1.05, 50)
ax.plot(
    x_fit,
    slope * x_fit + intercept,
    "-",
    color="C0",
    label=rf"Linear fit $|A_v|={slope:.1f}$",
)

ax.axhline(V_sat, color="C3", ls=":", lw=1.4, label=f"Saturation {V_sat:.2f} V")

ax.plot(Vi, Vo, "o", color="C1", ms=6, label="Measured", zorder=5)

ax.set_xlabel(r"Input $U_{i,pp}$ / V")
ax.set_ylabel(r"Output $U_{o,pp}$ / V")
ax.set_xlim(0, 2.1)
ax.set_ylim(0, 9)
ax.grid(True, ls=":", alpha=0.6)
ax.legend(loc="lower right", framealpha=0.95)

fig.tight_layout()
fig.savefig("transfer_characteristic.png", dpi=150)
print("saved transfer_characteristic.png")

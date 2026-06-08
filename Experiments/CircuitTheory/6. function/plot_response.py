"""绘制 RC 无源滤波器幅频/相频理论曲线与实测数据对比图"""

import numpy as np
import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt
from pathlib import Path

plt.rcParams.update({
    "figure.dpi": 150,
    "savefig.dpi": 300,
    "savefig.pad_inches": 0.1,
})

OUT = Path(__file__).parent / "figures"
OUT.mkdir(exist_ok=True)

# ── 元件参数 ──
R_LP, C_LP = 10e3, 10e-9      # 低通: R=10kΩ, C=10nF
R_HP, C_HP = 2e3, 10e-9       # 高通: R=2kΩ,  C=10nF
fc_lp = 1 / (2 * np.pi * R_LP * C_LP)  # 1591.5 Hz
fc_hp = 1 / (2 * np.pi * R_HP * C_HP)  # 7957.7 Hz

# ── 实测数据 ──
# 低通
f_lp  = np.array([260, 640, 1040, 1140, 1240, 1340, 1440, 1640, 1840, 2240, 3040, 7040, 10000])
Uo_lp = np.array([4.76, 4.48, 4.00, 3.88, 3.75, 3.63, 3.53, 3.29, 3.08, 2.73, 2.20, 1.75, 0.795])
Ui = 5.0
H_lp  = Uo_lp / Ui
phi_lp = np.array([-17.8, -25.6, -36.9, -39.1, -41.4, -43.4, -45.6, -48.9, -52.0, -56.9, -63.9, -76.7, -80.9])

# 高通
f_hp  = np.array([1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 8500, 9000, 10000, 11000, 12000, 20000, 30000])
Uo_hp = np.array([0.16, 0.689, 1.57, 2.32, 2.73, 3.05, 3.31, 3.53, 3.63, 3.72, 3.86, 3.97, 4.08, 4.49, 4.65])
H_hp  = Uo_hp / Ui
phi_hp = np.array([85, 82, 72, 62, 57, 52, 49, 46, 43, 42, 40, 37, 35, 26, 22])

# ── 理论曲线 ──
f_th_lp = np.logspace(np.log10(100), np.log10(20000), 500)
H_th_lp = 1 / np.sqrt(1 + (f_th_lp / fc_lp)**2)
phi_th_lp = -np.degrees(np.arctan(f_th_lp / fc_lp))

f_th_hp = np.logspace(np.log10(500), np.log10(50000), 500)
H_th_hp = 1 / np.sqrt(1 + (fc_hp / f_th_hp)**2)
phi_th_hp = np.degrees(np.arctan(fc_hp / f_th_hp))

# ── 绘图函数 ──
def plot_mag(f_th, H_th, f_exp, H_exp, fc, title, filename):
    fig, ax = plt.subplots(figsize=(5.5, 4))
    ax.semilogx(f_th, H_th, "b-", lw=1.5, label="Theory")
    ax.semilogx(f_exp, H_exp, "ro", ms=5, label="Measured")
    ax.axhline(0.707, color="gray", ls="--", lw=0.8, label="$|H|=0.707$")
    ax.axvline(fc, color="gray", ls="--", lw=0.8)
    ax.set_xlabel("Frequency $f$ / Hz")
    ax.set_ylabel("$|H(j\\omega)|$")
    ax.set_title(title)
    ax.legend(loc="best", fontsize=9)
    ax.set_ylim(0, 1.05)
    ax.grid(True, which="both", ls=":", alpha=0.5)
    fig.tight_layout()
    fig.savefig(OUT / filename)
    plt.close(fig)
    print(f"  -> {OUT / filename}")

def plot_phase(f_th, phi_th, f_exp, phi_exp, fc, phi_fc, title, filename):
    fig, ax = plt.subplots(figsize=(5.5, 4))
    ax.semilogx(f_th, phi_th, "b-", lw=1.5, label="Theory")
    ax.semilogx(f_exp, phi_exp, "ro", ms=5, label="Measured")
    ax.axhline(phi_fc, color="gray", ls="--", lw=0.8, label=f"$\\varphi={phi_fc}°$")
    ax.axvline(fc, color="gray", ls="--", lw=0.8)
    ax.set_xlabel("Frequency $f$ / Hz")
    ax.set_ylabel("Phase $\\varphi$ / °")
    ax.set_title(title)
    ax.legend(loc="best", fontsize=9)
    ax.grid(True, which="both", ls=":", alpha=0.5)
    fig.tight_layout()
    fig.savefig(OUT / filename)
    plt.close(fig)
    print(f"  -> {OUT / filename}")

# ── 生成 4 张图 ──
print("生成幅频/相频对比图...")
plot_mag(f_th_lp, H_th_lp, f_lp, H_lp, fc_lp,
         f"Low-pass ($R={R_LP/1e3:.0f}\\,\\mathrm{{k\\Omega}}$, $C={C_LP*1e9:.0f}\\,\\mathrm{{nF}}$, $f_c={fc_lp:.1f}\\,\\mathrm{{Hz}}$)",
         "lp_magnitude.pdf")

plot_phase(f_th_lp, phi_th_lp, f_lp, phi_lp, fc_lp, -45,
           f"Low-pass phase ($f_c={fc_lp:.1f}\\,\\mathrm{{Hz}}$)",
           "lp_phase.pdf")

plot_mag(f_th_hp, H_th_hp, f_hp, H_hp, fc_hp,
         f"High-pass ($R={R_HP/1e3:.0f}\\,\\mathrm{{k\\Omega}}$, $C={C_HP*1e9:.0f}\\,\\mathrm{{nF}}$, $f_c={fc_hp:.1f}\\,\\mathrm{{Hz}}$)",
         "hp_magnitude.pdf")

plot_phase(f_th_hp, phi_th_hp, f_hp, phi_hp, fc_hp, 45,
           f"High-pass phase ($f_c={fc_hp:.1f}\\,\\mathrm{{Hz}}$)",
           "hp_phase.pdf")

print("完成！")

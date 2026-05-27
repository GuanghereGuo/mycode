"""Generate RLC series resonance frequency response plots."""
import numpy as np
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt

L = 100e-3
C = 0.1e-6
f0 = 1 / (2 * np.pi * np.sqrt(L * C))

R_p = 110.0
V_s = 2.42 * (100 + R_p) / 100

f_exp_100 = np.array([1.0, 1.1, 1.2, 1.3, 1.4, 1.5, 1.61, 1.7, 1.8, 1.9, 2.0, 2.1, 2.2]) * 1e3
U_exp_100 = np.array([0.50, 0.63, 0.81, 1.07, 1.49, 2.07, 2.42, 2.07, 1.63, 1.31, 1.09, 0.93, 0.81])

f_exp_1000 = np.array([0.5, 0.7, 1.0, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9, 2.0, 2.1, 2.2, 3, 5, 10]) * 1e3
U_exp_1000 = np.array([1.54, 2.29, 3.23, 3.57, 3.87, 4.13, 4.35, 4.49, 4.56, 4.58, 4.54, 4.46, 4.35, 4.22, 4.08, 3.02, 1.73, 0.85])


def U_R(f, R_ext, R_extra):
    omega = 2 * np.pi * f
    R_total = R_ext + R_extra
    Z_mag = np.sqrt(R_total**2 + (omega * L - 1 / (omega * C))**2)
    return V_s * R_ext / Z_mag


f_s1 = np.linspace(400, 4000, 2000)
f_s2 = np.linspace(200, 12000, 2000)
OUT = '/home/guanghere/Code/mycode/Experiments/CircuitTheory/4. RC/figures'


def finish(ax, xlim, legend_fs=10):
    ax.set_xlabel('$f$ / kHz')
    ax.set_ylabel('$U_R$ / V')
    ax.axvline(f0 / 1e3, color='gray', ls='--', lw=0.8, alpha=0.5)
    ax.legend(loc='upper right', fontsize=legend_fs)
    ax.grid(True, alpha=0.3)
    ax.set_xlim(xlim)


# Plot 1: R=100 ideal
fig, ax = plt.subplots(figsize=(7, 4.5))
ax.plot(f_s1/1e3, U_R(f_s1, 100, 0), 'b-', lw=1.5, label=r'Ideal ($R=100\,\Omega$)')
ax.plot(f_exp_100/1e3, U_exp_100, 'ro', ms=5, zorder=5, label='Measured')
finish(ax, (0.4, 4.0))
fig.tight_layout()
fig.savefig(f'{OUT}/theory_r100_ideal.png', dpi=300, bbox_inches='tight')
plt.close()

# Plot 2: R=1000 ideal
fig, ax = plt.subplots(figsize=(7, 4.5))
ax.plot(f_s2/1e3, U_R(f_s2, 1000, 0), 'b-', lw=1.5, label=r'Ideal ($R=1000\,\Omega$)')
ax.plot(f_exp_1000/1e3, U_exp_1000, 'ro', ms=5, zorder=5, label='Measured')
finish(ax, (0.1, 12.0))
fig.tight_layout()
fig.savefig(f'{OUT}/theory_r1000_ideal.png', dpi=300, bbox_inches='tight')
plt.close()

# Plot 3: R=100 corrected
fig, ax = plt.subplots(figsize=(7, 4.5))
ax.plot(f_s1/1e3, U_R(f_s1, 100, 0), 'b--', lw=1, alpha=0.5, label=r'Ideal ($R_{eff}=100\,\Omega$)')
ax.plot(f_s1/1e3, U_R(f_s1, 100, R_p), 'b-', lw=1.5, label=r'Corrected ($R_{eff}=210\,\Omega$)')
ax.plot(f_exp_100/1e3, U_exp_100, 'ro', ms=5, zorder=5, label='Measured')
finish(ax, (0.4, 4.0), legend_fs=9)
fig.tight_layout()
fig.savefig(f'{OUT}/theory_r100_corrected.png', dpi=300, bbox_inches='tight')
plt.close()

# Plot 4: R=1000 corrected
fig, ax = plt.subplots(figsize=(7, 4.5))
ax.plot(f_s2/1e3, U_R(f_s2, 1000, 0), 'b--', lw=1, alpha=0.5, label=r'Ideal ($R_{eff}=1000\,\Omega$)')
ax.plot(f_s2/1e3, U_R(f_s2, 1000, R_p), 'b-', lw=1.5, label=r'Corrected ($R_{eff}=1110\,\Omega$)')
ax.plot(f_exp_1000/1e3, U_exp_1000, 'ro', ms=5, zorder=5, label='Measured')
finish(ax, (0.1, 12.0), legend_fs=9)
fig.tight_layout()
fig.savefig(f'{OUT}/theory_r1000_corrected.png', dpi=300, bbox_inches='tight')
plt.close()

print('Done. V_s=%.2f V, R_p=%.0f Ohm, f0=%.1f Hz' % (V_s, R_p, f0))

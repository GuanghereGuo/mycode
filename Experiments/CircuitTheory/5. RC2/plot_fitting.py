import numpy as np
from scipy.optimize import curve_fit
import matplotlib.pyplot as plt

t_data = np.array([-60, -5, 70, 160, 305, 805])
v_data = np.array([-968.4, 0, 508.1, 805, 945.6, 1000])

T0 = -60.0


def rc_response(t, V_inf, V_0, tau):
    return V_inf + (V_0 - V_inf) * np.exp(-(t - T0) / tau)


p0 = [1000, -968.4, 100]
bounds = ([500, -1500, 30], [1500, -200, 300])
popt, pcov = curve_fit(rc_response, t_data, v_data, p0=p0, bounds=bounds, maxfev=10000)
V_inf_fit, V_0_fit, tau_fit = popt
perr = np.sqrt(np.diag(pcov))

print("Fitting parameters:")
print(f"  V_inf = {V_inf_fit:.2f} +/- {perr[0]:.2f} mV")
print(f"  V_0   = {V_0_fit:.2f} +/- {perr[1]:.2f} mV")
print(f"  tau   = {tau_fit:.2f} +/- {perr[2]:.2f} us")
print()
print("Time constant comparison:")
print(f"  Theory:   tau = 100.00 us")
print(f"  63% law:  tau = 120.00 us")
print(f"  Fitting:  tau = {tau_fit:.2f} us")

residuals = v_data - rc_response(t_data, *popt)
ss_res = np.sum(residuals**2)
ss_tot = np.sum((v_data - np.mean(v_data)) ** 2)
r_squared = 1 - ss_res / ss_tot
print(f"  R^2 = {r_squared:.6f}")

t_fine = np.linspace(-80, 900, 500)
v_fine = rc_response(t_fine, *popt)

fig, ax = plt.subplots(figsize=(8, 5))

ax.plot(
    t_fine, v_fine, "b-", linewidth=1.5,
    label=rf"Fitted: $u_C(t) = {V_inf_fit:.0f} + ({V_0_fit:.0f} - {V_inf_fit:.0f})e^{{-(t+60)/{tau_fit:.1f}}}$"
)
ax.plot(t_data, v_data, "ro", markersize=7, zorder=5, label="Measured data")

v_63 = V_0_fit + 0.632 * (V_inf_fit - V_0_fit)
ax.axhline(y=v_63, color="gray", linestyle="--", linewidth=0.8, alpha=0.7)
t_63 = T0 + tau_fit
v_at_tau = rc_response(t_63, *popt)
ax.plot(
    t_63, v_at_tau, "g^", markersize=10, zorder=6,
    label=rf"63% level ($t$ = {t_63:.0f} $\mu$s, $u_C$ = {v_at_tau:.0f} mV)"
)

offsets = {
    -60: (20, -65),
    -5: (20, 45),
    70: (20, 40),
    160: (25, 35),
    305: (25, -55),
    805: (-130, -55),
}
for ti, vi in zip(t_data, v_data):
    ox, oy = offsets.get(ti, (15, 30))
    ax.annotate(
        f"({ti}, {vi:.1f})",
        xy=(ti, vi),
        xytext=(ti + ox, vi + oy),
        fontsize=7.5,
        arrowprops=dict(arrowstyle="-", color="gray", lw=0.5),
    )

ax.set_xlabel(r"$t$ / $\mu$s", fontsize=12)
ax.set_ylabel(r"$u_C$ / mV", fontsize=12)
ax.set_title(rf"RC Full Response: Exponential Fitting ($\tau$ = {tau_fit:.1f} $\mu$s, $R^2$ = {r_squared:.4f})", fontsize=11)
ax.legend(loc="lower right", fontsize=8.5)
ax.grid(True, alpha=0.3)
ax.set_xlim(-100, 900)

fig.tight_layout()
fig.savefig("figures/fitting_curve.pdf", dpi=300, bbox_inches="tight")
fig.savefig("figures/fitting_curve.png", dpi=300, bbox_inches="tight")
print(f"\nSaved to figures/fitting_curve.pdf and figures/fitting_curve.png")

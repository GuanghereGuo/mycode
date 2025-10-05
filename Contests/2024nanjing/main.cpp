#include <bits/stdc++.h>
using namespace std;

# define M_PI 3.14159265358979323846

struct Point {
    double x, y;
};

double hval(double th, const vector<Point>& pts) {
    double c = cos(th), s = sin(th);
    double mx = -1e100;
    for (auto& p : pts) mx = max(mx, p.x * c + p.y * s);
    return mx;
}

vector<double> get_cross(double c, const vector<Point>& pts) {
    vector<double> res;
    int n = pts.size();
    double eps = 1e-10, pi = M_PI;
    for (int i = 0; i < n; ++i) {
        double A = pts[i].x, B = pts[i].y;
        double r = hypot(A, B);
        if (abs(c) > r + eps) continue;
        double ac = max(-1.0, min(1.0, c / r));
        double delta = acos(ac);
        double alpha = atan2(B, A);
        double phi1 = alpha + delta, phi2 = alpha - delta;
        auto chk = [&](double ph) {
            ph = fmod(ph + 4 * pi, 2 * pi);
            if (ph < 0) ph += 2 * pi;
            double hv = hval(ph, pts);
            if (abs(hv - c) <= eps * max(1.0, abs(c))) res.push_back(ph);
        };
        chk(phi1);
        chk(phi2);
    }
    sort(res.begin(), res.end());
    auto it = unique(res.begin(), res.end(), [](double a, double b) { return abs(a - b) < 1e-9; });
    res.resize(it - res.begin());
    return res;
}

bool chk(double th, const vector<Point>& pts, double d) {
    double eps = 1e-10;
    double cu = cos(th), su = sin(th);
    double hu = -1e100;
    for (auto& p : pts) hu = max(hu, p.x * cu + p.y * su);
    if (hu < -eps) return false;
    double cn = -su, sn = cu;
    double hn = -1e100;
    for (auto& p : pts) hn = max(hn, p.x * cn + p.y * sn);
    if (hn < -d - eps) return false;
    double cnm = su, snm = -cu;
    double hnm = -1e100;
    for (auto& p : pts) hnm = max(hnm, p.x * cnm + p.y * snm);
    if (hnm < -d - eps) return false;
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(12);
    int n;
    double x0, y0, d, t;
    cin >> n >> x0 >> y0 >> d >> t;
    vector<Point> pts(n);
    for (int i = 0; i < n; ++i) cin >> pts[i].x >> pts[i].y;
    double pi = M_PI, per = 2 * pi;
    double th0 = atan2(y0, x0);
    auto cr0 = get_cross(0, pts);
    auto crd = get_cross(-d, pts);
    vector<double> crit;
    for (auto p : cr0) crit.push_back(fmod(p + 2 * pi, per));
    for (auto p : crd) {
        double s1 = fmod(p - pi / 2 + 2 * pi, per);
        double s2 = fmod(p + pi / 2 + 2 * pi, per);
        crit.push_back(s1);
        crit.push_back(s2);
    }
    sort(crit.begin(), crit.end());
    auto it = unique(crit.begin(), crit.end(), [](double a, double b) { return abs(a - b) < 1e-9; });
    crit.resize(it - crit.begin());
    int mc = crit.size();
    double pmea = 0;
    for (int i = 0; i < mc; ++i) {
        double p1 = crit[i];
        double p2 = crit[(i + 1) % mc];
        if (p2 < p1) p2 += per;
        double md = (p1 + p2) / 2;
        if (md > per) md -= per;
        double len = p2 - p1;
        if (chk(md, pts, d)) pmea += len;
    }
    double nf = floor(t / per);
    double ans = nf * pmea;
    double rt = fmod(t, per);
    if (rt > 0) {
        double lo = th0, hi = th0 + rt;
        vector<double> ap;
        for (auto ph : crit) {
            double df = lo - ph;
            double k = floor(df / per);
            double ca = ph + k * per;
            if (ca >= lo - 1e-10 && ca <= hi + 1e-10) ap.push_back(ca);
            ca = ph + (k + 1) * per;
            if (ca >= lo - 1e-10 && ca <= hi + 1e-10) ap.push_back(ca);
        }
        vector<double> iv = {lo, hi};
        for (auto p : ap) iv.push_back(p);
        sort(iv.begin(), iv.end());
        it = unique(iv.begin(), iv.end(), [](double a, double b) { return abs(a - b) < 1e-10; });
        iv.resize(it - iv.begin());
        double rmea = 0;
        for (size_t j = 0; j + 1 < iv.size(); ++j) {
            double p1 = iv[j], p2 = iv[j + 1];
            if (p2 - p1 < 1e-12) continue;
            double md = (p1 + p2) / 2;
            if (chk(md, pts, d)) rmea += p2 - p1;
        }
        ans += rmea;
    }
    cout << ans << '\n';
}

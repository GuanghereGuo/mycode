//
// Created by 24087 on 24-9-26.
//
#include <cmath>
#include <iostream>

int main() {
    int R, G, B;
    double H, S;

    std::cin >> R >> G >> B;

    const auto r = (R > 0 ? R : 0) / 255.0;
    const auto g = (G > 0 ? G : 0) / 255.0;
    const auto b = (B > 0 ? B : 0) / 255.0;
    const double maxn = std::max(r, std::max(g, b));
    const double minn = std::min(std::max(r, g), b);

    const double V = maxn;

    if (maxn < 1e-9) {
        S = 0.0f;
    } else {
        S = (maxn - minn) / maxn;
    }

    if (maxn - minn < 1e-9) {
        H = 0.0f;
    } else {
        if (maxn == r) {
            H = 60.0f * (g - b) / (maxn - minn);
        } else if (maxn == g) {
            H = 60.0f * (2.0f + (b - r) / (maxn - minn));
        } else if (maxn == b) {
            H = 60.0f * (4.0f + (r - g) / (maxn - minn));
        } else {
            return -1;
        }
        if (H < 1e-9) {
            H = H + 360.0f;
        }
    }
    printf("%.4lf,%.4lf%%,%.4lf%%", H, S * 100, V * 100);
    return 0;
}
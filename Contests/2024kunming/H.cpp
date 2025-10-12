//
// Created by guanghere on 2025/10/12.
//
#include <bits/stdc++.h>

# define M_PI		3.14159265358979323846

void solve() {
    int n, k;
    std::cin >> n >> k;
    std::vector<double> theta(2 * n);
    for (int i = 0, x, y; i < n; ++i) {
        std::cin >> x >> y;
        theta[i] = std::atan2(y, x);
        theta[i + n] = theta[i] + 2 * M_PI;
    }
    std::sort(theta.begin(), theta.end());
    double ans = 0;
    for (int i = 0; i < n; i++) {
        ans = std::max(ans, theta[i + k] - theta[i]);
    }
    std::cout << std::fixed << std::setprecision(10) << ans << "\n";
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }
}
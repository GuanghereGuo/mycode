//
// Created by guanghere on 2026/7/17.
//
#include <iostream>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;

    while (t--) {
        int n;
        std::cin >> n;
        std::cout << 2 * n << '\n';
        double d = 0.0101;
        for (int i = 0; i < n; i++) {
            double x, y;
            x = (i % 10) * d;
            y = (i / 10) * d;
            std::cout << x << ' ' << y << " 0\n";
            std::cout << x << ' ' << y << " 1\n";
        }
    }
}
//
// Created by guanghere on 2026/4/19.
//
#include <bits/stdc++.h>

int main() {
    int n;
    std::cin >> n;

    int max1 = 0, max0 = 0;
    std::vector<std::pair<int, int>> v;

    for (int i = 1, x, y; i <= n; i++) {
        std::cin >> x >> y;
        v.emplace_back(x, y);
        max1 = std::max(max1, y);
        max0 = std::max(max0, x - y);
    }

    std::cout << max0 + max1 << std::endl;

    // print max1 '1'
    for (int i = 1; i <= max1; i++) {
        std::cout << '1';
    }
    // print max0 '0'
    for (int i = 1; i <= max0; i++) {
        std::cout << '0';
    }
    std::cout << std::endl;
    for (auto [x, y] : v) {
        std::cout << max1 - y << '\n';
    }
    return 0;
}
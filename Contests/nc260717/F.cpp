//
// Created by guanghere on 2026/7/17.
//
#include <iostream>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, k, x;
    std::cin >> n >> k >> x;

    std::vector<int> p(n);
    for (int &value : p) {
        std::cin >> value;
    }

    const int shift = (x - p[k] + n) % n;
    for (int i = 0; i < n; ++i) {
        if (i > 0) {
            std::cout << ' ';
        }
        std::cout << (p[i] + shift) % n;
    }
    std::cout << '\n';

    return 0;
}

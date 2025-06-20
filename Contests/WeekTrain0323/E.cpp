//
// Created by guanghere on 25-3-23.
//
#include <iostream>

using ull = unsigned long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int t;
    std::cin >> t;
    while (t--) {
        ull n, a, b;
        std::cin >> n;
        if (n & 1) {
            std::cout << "-1\n";
        } else {
            a = n >> 1;
            b = (1ull << 60) - a;
            std::cout << a << ' ' << b << '\n';
        }
    }
}
//
// Created by guanghere on 2025/10/6.
//
#include <bits/stdc++.h>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;
    while (t--) {
        int n;
        std::cin >> n;
        std::cout << (n % 3 == 0 ? 0 : 3 - n % 3) << '\n';
    }
}
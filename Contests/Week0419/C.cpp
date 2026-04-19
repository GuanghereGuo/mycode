//
// Created by guanghere on 2026/4/19.
//
#include <bits/stdc++.h>

int main() {

    int t;
    std::cin >> t;

    constexpr long long mod = 998244353;
    while (t--) {
        long long n;
        std::cin >> n;
        std::cout << n * (n + 1) % mod * (2 * n + 1) % mod * 166374059 % mod << std::endl;
    }


}
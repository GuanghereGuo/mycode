//
// Created by guanghere on 2026/4/19.
//
#include <bits/stdc++.h>

#define int long long

signed main() {
 
    int t;
    std::cin >> t;

    while (t--) {
        int n, maxn = 0;
        long long sum = 0;
        std::cin >> n;
        for (int i = 1, x; i <= n; i++) {
            std::cin >> x;
            sum += x;
            maxn = std::max(maxn, x);
        }
        if (2 * maxn > sum) {
            std::cout << "YES\n";
            continue;
        }
        std::cout << (n % 2 ? "NO\n" : "YES\n");
    }

}
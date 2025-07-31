//
// Created by guanghere on 25-7-27.
//
#include <bits/stdc++.h>

#define int long long

signed main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;

    while (t--) {
        int n;
        std::cin >> n;
        int min_n =  INT_MAX / 2;
        bool flag = true;
        for (int i = 1, x; i <= n; ++i) {
            std::cin >> x;
            if (x >= min_n * 2) {
                flag = false;
            }
            min_n = std::min(min_n, x);
        }
        if (flag) {
            std::cout << "YES\n";
        } else {
            std::cout << "NO\n";
        }
    }
}
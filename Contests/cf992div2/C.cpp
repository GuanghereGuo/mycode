//
// Created by 24087 on 24-12-8.
//
//
// Created by 26444 on 24-12-8.
//
#include<iostream>
#include <cmath>
#include <vector>

#define int long long

signed main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int t;
    std::cin >> t;
    while(t--) {
        int n, k;
        std::cin >> n >> k;
        if (std::log2(k) > n - 1) {
            std::cout << -1 << std::endl;
            continue;
        }
        std::vector<int> a(n + 1);

        for (int i = 1; i <= n - 1 - 60; i++) {
            a[i] = i;
        }
        int l = 1, r = 1ll << std::min(60ll, n - 1);
        int l_idx = std::max(n - 60, 1ll), r_idx = n, cnt = std::max(n - 60, 1ll);
        while (l + 1 != r) {
            int mid = (l + r) / 2;
            if (mid < k) {
                a[r_idx--] = cnt++;
                l = mid;
            } else {
                a[l_idx++] = cnt++;
                r = mid;
            }
        }
        a[r_idx] = cnt;
        std::cerr << r_idx << '\n';
        for (int i = 1; i <= n; i++) {
            std::cout << a[i] << ' ';
        }
        std::cout << std::endl;
    }

}


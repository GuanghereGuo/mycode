//
// Created by 24087 on 24-10-3.
//
#include <string.h>

#include <algorithm>
#include <array>
#include <bit>
#include <iostream>
#include <numeric>
#include <vector>

std::array<std::array<unsigned, static_cast<int>(1e6 + 5)>, 23> dp;

signed main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int t;
    std::cin >> t;

    while (t--) {
        memset(dp.data(), 0, sizeof(dp));
        int n;
        std::cin >> n;
        std::vector<int> vec(n);
        for (int i = 0, x; i < n; i++) {
            std::cin >> x;
            dp[0][x]++;
        }

        for(int i = 1; i <= 20; i++) {
            for(int j = 1; j <= 1e6; j++) {
                dp[i][j] = dp[i - 1][j];
                if((j >> (i - 1)) & 1)
                    dp[i][j] += dp[i - 1][j - (1 << (i - 1))];
            }
        }
        long long ans = 0;
        for(int i = 1; i <= 1e6; i++) {
            ans += static_cast<long long>(dp[0][i]) * dp[20][i];
        }
        std::cout << ans << '\n';
    }
}
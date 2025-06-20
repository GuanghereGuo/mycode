//
// Created by 24087 on 24-9-28.
//
#include <iostream>
#include <vector>

constexpr int mod = 1000000007;

signed main() {

    int n, m;
    std::cin >> n >> m;

    std::vector<int> dp(n + 1);
    std::vector<bool> forbidden(n + 1);

    for(int i = 1; i <= m; i++) {
        int x;
        std::cin >> x;
        forbidden[x] = true;
    }

    dp[0] = 1;
    dp[1] = forbidden[1] ? 0 : 1;

    for(int i = 2; i <= n; i++) {
        if(forbidden[i])
            continue;
        dp[i] = (dp[i - 1] + dp[i - 2]) % mod;
    }

    std::cout << dp[n];

}
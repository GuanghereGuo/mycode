//
// Created by guanghere on 25-7-26.
//
#include <iostream>
#include <vector>

using ull = unsigned long long;
using ll = long long;

constexpr int MOD = 1e9 + 7;
constexpr int MAXB = 61;

//dp[i] = sum_{j=1 to i} (dp[j-1] * (p[i] ^ p[j-1]))
//dp[i] = sum_{k=0 to 60} (2^k * sum_{j=1 to i} (dp[j-1] * bit_k(p[i] ^ p[j-1])))

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<ll> p2(MAXB);
    p2[0] = 1;
    for (int i = 1; i < MAXB; ++i) {
        p2[i] = (p2[i - 1] * 2) % MOD;
    }

    std::vector<ll> s0(MAXB, 0);
    std::vector<ll> s1(MAXB, 0);

    for (int k = 0; k < MAXB; ++k) {
        s0[k] = 1;
    }

    ull pxor = 0;
    ll ans = 0;

    for (int i = 1; i <= n; ++i) {
        ull x;
        std::cin >> x;
        pxor ^= x;

        ll cur = 0;
        for (int k = 0; k < MAXB; ++k) {
            ll val;
            if ((pxor >> k) & 1) {
                val = (p2[k] * s0[k]) % MOD;
            } else {
                val = (p2[k] * s1[k]) % MOD;
            }
            cur = (cur + val) % MOD;
        }
        for (int k = 0; k < MAXB; ++k) {
            if ((pxor >> k) & 1) {
                s1[k] = (s1[k] + cur) % MOD;
            } else {
                s0[k] = (s0[k] + cur) % MOD;
            }
        }

        if (i == n) {
            ans = cur;
        }
    }

    std::cout << ans << std::endl;

    return 0;
}
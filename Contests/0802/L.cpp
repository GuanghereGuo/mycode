//
// Created by guanghere on 25-8-2.
//
//
// Created by guanghere on 25-8-2.
//
#include <bits/stdc++.h>

using ll = long long;

constexpr ll mod = 998244353;

ll add(ll x, ll y) {
    return (x % mod + y % mod) % mod;
}
ll mul(ll x, ll y) {
    return (x % mod * (y % mod)) % mod;
}

ll pow(ll x, ll y) {
    ll res = 1;
    x %= mod;
    while (y > 0) {
        if (y & 1) {
            res = mul(res, x);
        }
        x = mul(x, x);
        y >>= 1;
    }
    return res;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t;
    std::cin >> t;
    while (t--) {
        ll a, b;
        std::cin >> a >> b;
        if ((a & 1) + (b & 1) == 0) {
            std::cout << "1\n";
        } else if ((a & 1) + (b & 1) == 2) {
            std::cout << pow(2ll, a + b - 2ll) << "\n";
        } else {
            std::cout << pow(2ll, (a & 1 ? b : a) - 1ll) << "\n";
        }
    }
}
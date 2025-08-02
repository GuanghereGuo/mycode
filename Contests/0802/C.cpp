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
    int n, k;
    std::string s;
    std::cin >> n >> k;
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }
    std::cin >> s;
    int len = s.size();
    ll base = 0;
    if (s.back() == 's') {
        for (int i = 0; i < n; ++i) {
            base = add(base, a[i]);
        }
    }  else {
        base = 1;
        for (int i = 0; i < n; ++i) {
            base = mul(base, a[i]);
        }
    }

    for (int i = len - 2; i >= 0; --i) {
        if (s[i] == 's') {
            base = mul(base, n);
        } else {
            base = pow(base, n);
        }
    }
    std::cout << base << std::endl;
}
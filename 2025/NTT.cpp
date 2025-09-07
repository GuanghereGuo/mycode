//
// Created by guanghere on 25-8-7.
//
#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using ll = long long;

namespace ntt {
constexpr int mod = 998244353;
constexpr int G = 3;

std::map<int, std::vector<ll>> w_cache;
std::map<int, std::vector<int>> rev_cache;

ll power(ll base, ll exp) {
    ll res = 1;
    base %= mod;
    while (exp > 0) {
        if (exp % 2 == 1) res = (res * base) % mod;
        base = (base * base) % mod;
        exp /= 2;
    }
    return res;
}

ll modInverse(ll n) { return power(n, mod - 2); }

void transform(std::vector<ll>& a, bool invert) {
    int n = a.size();

    if (rev_cache.find(n) == rev_cache.end()) {
        int log_n = 0;
        while ((1 << log_n) < n) log_n++;
        std::vector<int> rev(n);
        for (int i = 0; i < n; i++) {
            rev[i] = 0;
            for (int j = 0; j < log_n; j++) {
                if ((i >> j) & 1) rev[i] |= 1 << (log_n - 1 - j);
            }
        }
        rev_cache[n] = std::move(rev);

        std::vector<ll> w(n);
        ll wn = power(G, (mod - 1) / n);
        w[0] = 1;
        for (int i = 1; i < n; i++) w[i] = (w[i - 1] * wn) % mod;
        w_cache[n] = std::move(w);
    }

    const auto& rev = rev_cache.at(n);
    for (int i = 0; i < n; i++) {
        if (i < rev[i]) std::swap(a[i], a[rev[i]]);
    }

    const auto& w_table = w_cache.at(n);
    for (int len = 2; len <= n; len <<= 1) {
        int step = n / len;
        for (int i = 0; i < n; i += len) {
            for (int j = 0; j < len / 2; j++) {
                ll u = a[i + j];
                ll v = (a[i + j + len / 2] * w_table[j * step]) % mod;
                a[i + j] = (u + v) % mod;
                a[i + j + len / 2] = (u - v + mod) % mod;
            }
        }
    }

    if (invert) {
        std::reverse(a.begin() + 1, a.end());
        ll n_inv = modInverse(n);
        for (ll& x : a) {
            x = (x * n_inv) % mod;
        }
    }
}
}

void solve() {
    std::string sa, sb;
    std::cin >> sa >> sb;

    if (sa == "0" || sb == "0") {
        std::cout << "0\n";
        return;
    }

    int n = sa.length();
    int m = sb.length();

    std::vector<ll> a(n), b(m);
    for (int i = 0; i < n; ++i)
        a[i] = sa[n - 1 - i] - '0';
    for (int i = 0; i < m; ++i)
        b[i] = sb[m - 1 - i] - '0';

    int len = 1;
    while (len < n + m)
        len <<= 1;

    a.resize(len, 0);
    b.resize(len, 0);

    ntt::transform(a, false);
    ntt::transform(b, false);

    std::vector<ll> c(len);
    for (int i = 0; i < len; ++i) {
        c[i] = (a[i] * b[i]) % ntt::mod;
    }

    ntt::transform(c, true);

    int res_len = n + m + 50;
    c.resize(res_len, 0);

    for (int i = 0; i < res_len - 2; ++i) {
        ll val = c[i];

        ll r = val % 2;
        if (r < 0) r += 2;

        ll q = (val - r) / 2;

        c[i] = r;
        c[i + 2] -= q;
    }

    int first_digit = res_len - 1;
    while (first_digit > 0 && c[first_digit] == 0) {
        first_digit--;
    }

    for (int i = first_digit; i >= 0; --i) {
        std::cout << c[i];
    }
    std::cout << "\n";
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}

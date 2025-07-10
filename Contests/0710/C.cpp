//
// Created by guanghere on 25-7-10.
//
#include <bits/stdc++.h>

using ll = long long;

bool check(ll w, ll m, ll n) {
    if (w >= n) return true;
    ll s = 0;
    while (m > 0 && s < n) {
        ll a = std::min(w, s + 1);
        if (a >= w)
            return s + m * w >= n;
        s += a;
        m--;
    }
    return s >= n;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int T;
    std::cin >> T;
    while (T--) {
        ll n, m;
        std::cin >> n >> m;

        if (m >= n) {
            std::cout << 1 << '\n';
            continue;
        }

        ll max_sum = (m < 60) ? (1LL << m) - 1 : LLONG_MAX;
        if (max_sum < n) {
            std::cout << -1 << '\n';
            continue;
        }

        ll left = 1, right = n;
        while (left < right) {
            ll mid = left + (right - left) / 2;
            if (check(mid, m, n)) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }

        if (check(left, m, n)) {
            std::cout << left << '\n';
        } else {
            std::cout << -1 << '\n';
        }
    }
    return 0;
}

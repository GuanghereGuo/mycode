//
// Created by guanghere on 25-7-31.
//
#include <bits/stdc++.h>

class BIT {
    using ll = long long;
    int n;
    std::vector<ll> tr;
    constexpr static int low_bit(const int x) {
        return x & -x;
    }

public:
    explicit BIT(int n): n(n), tr(n + 1) {}
    void add(int idx, ll val) {
        for(int i = idx; i <= n; i += low_bit(i)) {
            tr[i] += val;
        }
    }
    ll query(int idx) {
        ll res = 0;
        for(int i = idx; i; i -= low_bit(i)) {
            res += tr[i];
        }
        return res;
    }
    ll query(int l, int r) {
        return query(r) - query(l - 1);
    }
};

bool check(const std::string &s) {
    int cnt = 0;
    for (char c : s) {
        if (c == '(') {
            cnt++;
        } else {
            cnt--;
        }
        if (cnt < 0) {
            return false;
        }
    }
    return cnt == 0;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int T;
    std::cin >> T;
    while (T--) {
        int n, m;
        std::cin >> n >> m;
        int cnt = m;
        BIT bit(2 * n);
        std::string s(2 * n, '0');
        std::vector<std::pair<int, int>> vec(m);
        for (int i = 0; i < m; ++i) {
            std::cin >> vec[i].first >> vec[i].second;
        }
        std::ranges::sort(vec);
        for (int i = m - 1; i >= 0; --i) {
            if (bit.query(vec[i].first, vec[i].second)) {
                cnt--;
                continue;
            }
            bit.add(vec[i].first, 1);
            s[vec[i].first - 1] = '(';
        }
        if (cnt > n) {
            std::cout << "-1\n";
            continue;
        }
        for (int i = 0; i < 2 * n; ++i) {
            if (s[i] == '0') {
                if (cnt < n) {
                    s[i] = '(';
                    cnt++;
                } else {
                    s[i] = ')';
                }
            }
        }
        if (!check(s)) {
            std::cout << "-1\n";
            continue;
        }
        std::cout << s << "\n";
    }
}
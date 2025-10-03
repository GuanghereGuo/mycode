//
// Created by guanghere on 2025/10/3.
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
    BIT(int n): n(n), tr(n + 1) {}
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

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t;
    std::cin >> t;
    while (t--) {
        int n, q;
        std::cin >> n >> q;
        std::vector<int> vec(n + 1);
        BIT bit1(n), bit(n);
        for (int i = 1; i <= n; ++i) {
            std::cin >> vec[i];
            if (vec[i]) {
                bit.add(i, 1);
            }
        }
        for (int i = 2; i <= n; ++i) {
            if (vec[i] == vec[i - 1]) {
                bit1.add(i, 1);
            }
        }

        for (int ii = 1; ii <= q; ++ii) {
            int l, r;
            std::cin >> l >> r;
            int len = r - l + 1;
            if (len % 3 != 0 || bit.query(l, r) % 3 != 0) {
                std::cout << "-1\n";
            } else {
                std::cout << len / 3 + (bit1.query(l + 1, r) == 0) << "\n";
            }
        }

    }
}
//
// Created by 24087 on 24-10-12.
//
#include <iostream>
#include <vector>

class BIT {
    using ll = long long;
    int n;
    std::vector<ll> tr;
    constexpr static int low_bit(const int x) { return x & -x; }

public:
    BIT(int n) : n(n), tr(n + 1) {}
    void add(int idx, ll val) {
        for (int i = idx; i <= n; i += low_bit(i)) {
            tr[i] += val;
        }
    }
    ll query(int idx) {
        ll res = 0;
        for (int i = idx; i; i -= low_bit(i)) {
            res += tr[i];
        }
        return res;
    }
    ll query(int l, int r) { return query(r) - query(l - 1); }
};

int main() {
    int n, m;
    std::cin >> n >> m;
    BIT bit(n);
    for (int i = 1, x; i <= n; i++) {
        std::cin >> x;
        bit.add(i, x);
    }
    for(int i = 1, opt, x, y; i <= m; i++) {
        std::cin >> opt >> x >> y;
        if (opt == 1) {
            bit.add(x, y);
        } else {
            std::cout << bit.query(x, y) << '\n';
        }
    }
}
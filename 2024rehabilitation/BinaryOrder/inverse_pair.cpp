//
// Created by guanghere on 24-12-21.
//
#include <iostream>
#include <vector>
#include <algorithm>

class BIT {
    using ll = long long;
    int n;
    std::vector<ll> tr;
    constexpr static int low_bit(const int x) { return x & -x; }

public:
    explicit BIT(const int n) : n(n), tr(n + 1) {}
    void add(const int idx, const ll val) {
        for (int i = idx; i <= n; i += low_bit(i)) {
            tr[i] += val;
        }
    }
    [[nodiscard]] ll query(const int idx) const {
        ll res = 0;
        for (int i = idx; i; i -= low_bit(i)) {
            res += tr[i];
        }
        return res;
    }
    [[nodiscard]] ll query(const int l, const int r) const { return query(r) - query(l - 1); }
};

// (a_i, i) < (a_j, j) if a_i < a_j and i > j

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n;
    std::cin >> n;
    std::vector<std::pair<int, int>> vec(n + 1);
    for (int i = 1; i <= n; i++) {
        std::cin >> vec[i].first;
        vec[i].second = i;
    }
    std::sort(vec.begin() + 1, vec.end());

    BIT bit(n);
    long long ans = 0;
    for(int i = 1; i <= n; i++) {
        ans += bit.query(vec[i].second + 1, n);
        bit.add(vec[i].second, 1);
    }
    std::cout << ans << '\n';
}
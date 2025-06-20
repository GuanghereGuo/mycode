#include <iostream>
#include <vector>

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

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n;
    std::cin >> n;

    BIT bit(32001);
    std::vector<int> ans(n);

    for (int i = 1, x, y; i <= n; i++) {
        std::cin >> x >> y;
        ans[bit.query(1, x + 1)]++;
        bit.add(x + 1, 1);
    }
    for (int i = 0; i < n; i++) {
        std::cout << ans[i] << '\n';
    }
}
//POJ 2352 Stars

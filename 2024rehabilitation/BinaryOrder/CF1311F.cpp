//
// Created by guanghere on 24-12-23.
//
#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

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

template<typename T>
void discretization_linear(std::vector<T> &a) {
    a[0] = std::numeric_limits<T>::min();
    struct Node {
        T val;
        int id;
        bool operator<(const Node &rhs) const { return val < rhs.val; }
    };
    std::vector<Node> vec;
    for (int i = 0; i < a.size(); i++) {
        vec.push_back({a[i], i});
    }
    std::sort(vec.begin(), vec.end());
    for (int i = 0, cnt = 0; i < vec.size(); i++) {
        a[vec[i].id] = cnt;
        if (i + 1 < vec.size() && vec[i].val != vec[i + 1].val) {
            cnt++;
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<int> x(n + 1), v(n + 1);
    for (int i = 1; i <= n; i++) {
        std::cin >> x[i];
    }
    for (int i = 1; i <= n; i++) {
        std::cin >> v[i];
    }

    discretization_linear(v);

    BIT bit_number(n), bit_distance(n);

    std::vector<std::pair<int, int>> vec(n + 1);
    for (int i = 1; i <= n; i++) {
        vec[i] = {x[i], v[i]};
    }

    std::sort(vec.begin() + 1, vec.end());

    long long ans = 0;

    for (int i = 1; i <= n; i++) {
        long long  number = bit_number.query(vec[i].second);
        long long distance = bit_distance.query(vec[i].second);
        ans += 1LL * number * vec[i].first - distance;
        bit_number.add(vec[i].second, 1);
        bit_distance.add(vec[i].second, vec[i].first);
    }
    std::cout << ans;
}
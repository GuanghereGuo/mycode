//
// Created by guanghere on 25-7-12.
//
#include <bits/stdc++.h>

class EBIT {
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

    int n;
    BIT d, di;
public:
    explicit EBIT(int n): n(n), d(n), di(n) {}
    //sum(r) = d_sum * (r + 1) - di_sum
    using ll = long long;

    ll query(int idx) {
        return d.query(idx) * (idx + 1) - di.query(idx);
    }
    ll query(int l, int r) {
        return query(r) - query(l - 1);
    }

    void add(int l, int r, int val) {
        d.add(l, val);
        d.add(r + 1, -val);

        di.add(l, val * l);
        di.add(r + 1, -val * (r + 1));
    }
    void add(int idx, int val) {
        add(idx, idx, val);
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, q;
    std::cin >> n >> q;
    std::set<int> s;
    std::vector<std::pair<int, int>> v(n + 1);
    std::vector<int> query(q + 1);
    for (int i = 1; i <= n; ++i) {
        std::cin >> v[i].first >> v[i].second;
        s.insert(v[i].first);
        s.insert(v[i].second);
    }
    for (int i = 1; i <= q; ++i) {
        std::cin >> query[i];
        s.insert(query[i]);
    }

    std::vector<int> d(s.begin(), s.end());
    std::unordered_map<int, int> mp;
    for (int i = 0; i < d.size(); ++i) {
        mp[d[i]] = i + 1;
    }
    EBIT bit(d.size());
    for (int i = 1; i <= n; ++i) {
        int l = mp[v[i].first], r = mp[v[i].second];
        //std::cerr << l << " " << r << std::endl;
        bit.add(l, r, 1);
    }
    for (int i = 1; i <= q; ++i) {
        int idx = mp[query[i]];
        std::cout << bit.query(idx, idx) << '\n';
    }
}
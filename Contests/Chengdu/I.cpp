//
// Created by 24087 on 24-11-3.
//
#include <algorithm>
#include <vector>
#include <iostream>
#include <numeric>
#include <set>
#include <unordered_map>
#include <cmath>

class ChthollyTree {
    struct Node {
        int l;
        mutable int r;
        Node(int l, int r) : l(l), r(r) {}
        bool operator<(const Node &x) const { return l < x.l; }
    };
    int n;
    std::set<Node> s;

    auto split(int x) {
        auto it = s.lower_bound(Node(x, 0));
        if (it != s.end() && it->l == x) {
            return it;
        }
        --it;
        int l = it->l, r = it->r;
        s.erase(it);
        s.emplace(l, x - 1);
        return s.emplace(x, r).first;
    }

   public:
    explicit ChthollyTree(const int n) : n(n) { s.emplace(1, n); }
    int get_point_gcd() {
        if(s.size() == 1) {
            return -1;
        }
        int gcd = s.begin()->r;
        for (auto [l, r] : s) {
            if(r == n) {
                return gcd;
            }
            gcd = std::gcd(gcd, r);
            if (gcd == 1) {
                return 1;
            }
        }
        return gcd;
    }
    void merge(int x) {  // 右侧区间的起点
        auto it = s.lower_bound(Node(x, 0));
        if (it == s.begin() || it->l != x || it == s.end()) {
            return;
        }
        int r = it->r;
        s.erase(it--);
        it->r = r;
    }
    void cut(int x) { split(x); }
};

//计算因子个数
int factor_count(int n) {
    static std::unordered_map<int, int> mp;
    if(mp[n]) {
        return mp[n];
    }
    int count = 0;
    for (int i = 1; i <= sqrt(n); i++) {
        if (n % i == 0) {
            if (n / i == i) {
                count++;
            } else {
                count += 2;
            }
        }
    }
    return mp[n] = count;
}


signed main() {
    std::ios::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;
    while (t--) {
        int n, q;
        std::cin >>  n >> q;
        ChthollyTree tree(n);
        std::vector<int> vec(n + 1);
        for (int i = 1; i <= n; ++i) {
            std::cin >> vec[i];
        }
        for (int i = 2; i <= n; ++i) {
            if(vec[i] < vec[i - 1]) {
                tree.cut(i);
            }
        }

        int tmp = tree.get_point_gcd();
        if(tmp == -1) {
            std::cout << n << '\n';
        } else
            std::cout << factor_count(tmp) << '\n';

        for(int i = 1; i <= q; i++) {
            int idx, val;
            std::cin >> idx >> val;
            vec[idx] = val;

            if(idx == 1) {
                if(vec[2] < vec[1]) {
                    tree.cut(2);
                } else {
                    tree.merge(2);
                }
            } else if(idx == n) {
                if(vec[n] < vec[n - 1]) {
                    tree.cut(n);
                } else {
                    tree.merge(n);
                }
            } else {
                if(vec[idx - 1] > vec[idx]) {
                    tree.cut(idx);
                } else {
                    tree.merge(idx);
                }
                if(vec[idx] > vec[idx + 1]) {
                    tree.cut(idx + 1);
                } else {
                    tree.merge(idx + 1);
                }
            }
            tmp = tree.get_point_gcd();
            if(tmp == -1) {
                std::cout << n << '\n';
            } else
                std::cout << factor_count(tmp) << '\n';
        }
    }
}
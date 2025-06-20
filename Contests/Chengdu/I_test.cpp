//
// Created by 24087 on 24-11-3.
//
#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <numeric>
#include <set>
#include <vector>

class ChthollyTree {
    struct Node {
        int l;
        mutable int r;
        Node(int l, int r) : l(l), r(r) {}
        bool operator<(const Node &x) const { return l < x.l; }
    };
    int n;
    std::set<Node> s;
    std::map<int, int> lens;  // 维护除了最后一个区间的长度

    void del_range_len(int l, int r) {
        if(r==n)
            return;
        if (--lens[r - l + 1] == 0) {
            lens.erase(r - l + 1);
        }
    }

    void add_range_len(int l, int r) {
        if(r == n)
            return;
        ++lens[r - l + 1];
    }

    auto split(int x) {
        auto it = s.lower_bound(Node(x, 0));
        if (it != s.end() && it->l == x) {
            return it;
        }
        --it;
        int l = it->l, r = it->r;

        del_range_len(l, r);
        add_range_len(x, r);
        add_range_len(l, x - 1);

        s.erase(it);
        s.emplace(l, x - 1);
        return s.emplace(x, r).first;
    }

   public:
    explicit ChthollyTree(const int n) : n(n) { s.emplace(1, n); }
    int get_len_gcd() {
        if (lens.empty()) {
            return -1;
        }
        int gcd = lens.begin()->first;
        for (auto [len, cnt] : lens) {
            gcd = std::gcd(gcd, len);
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
        del_range_len(x, r);
        s.erase(it--);
        del_range_len(it->l, it->r);
        it->r = r;
        add_range_len(it->l, r);
    }
    void cut(int x) { split(x); }
};


int factor_count(int n) {
    // static std::map<int, int> mp;
    // if (mp[n]) {
    //     return mp[n];
    // }
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
    //return mp[n] = count;
    return count;
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

        auto print = [&]() {
            int tmp = tree.get_len_gcd();
            if(tmp == -1) {
                std::cout << n << '\n';
            } else
                std::cout << factor_count(tmp) << '\n';
        };

        print();

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
            print();
        }
    }
}
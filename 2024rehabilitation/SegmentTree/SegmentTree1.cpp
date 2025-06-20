//
// Created by 24087 on 24-10-12.
//
#include <functional>
#include <iostream>
#include <vector>
#include <climits>

template <typename T>
class SegmentTree {
    struct Node {
        T lzy = 0, val = 0;
    };
    int n;
    long long mod;
    std::vector<Node> tree;
    void pull_up(int now) {
        tree[now].val = (tree[now << 1].val + tree[now << 1 | 1].val) % mod;
    }
    void push_down(int now, int l, int r) {
        if (!tree[now].lzy) {
            return;
        }
        int mid = l + (r - l) / 2;
        (tree[now << 1].val += tree[now].lzy * (mid - l + 1)) %= mod;
        (tree[now << 1 | 1].val += tree[now].lzy * (r - mid)) %= mod;
        (tree[now << 1].lzy += tree[now].lzy) %= mod;
        (tree[now << 1 | 1].lzy += tree[now].lzy) %= mod;
        tree[now].lzy = 0;
    }
    void add(int now, int l, int r, int tar_l, int tar_r, T val) {
        if (tar_l <= l && r <= tar_r) {
            (tree[now].val += val * (r - l + 1)) %= mod;
            (tree[now].lzy += val) %= mod;
            return;
        }
        push_down(now, l, r);
        int mid = l + (r - l) / 2;
        if (tar_l <= mid) {
            add(now << 1, l, mid, tar_l, tar_r, val);
        }
        if (tar_r > mid) {
            add(now << 1 | 1, mid + 1, r, tar_l, tar_r, val);
        }
        pull_up(now);
    }
    T query(int now, int l, int r, int tar_l, int tar_r) {
        if (tar_l <= l && r <= tar_r) {
            return tree[now].val;
        }
        push_down(now, l, r);
        int mid = l + (r - l) / 2;
        T res = 0;
        if (tar_l <= mid) {
            (res += query(now << 1, l, mid, tar_l, tar_r)) %= mod;
        }
        if (tar_r > mid) {
            (res += query(now << 1 | 1, mid + 1, r, tar_l, tar_r)) %= mod;
        }
        return res;
    }

   public:
    explicit SegmentTree(int n, T p = 1e18) : n(n), mod(p), tree(n << 2) {}
    explicit SegmentTree(const std::vector<T> &arr, T p = 1e18)
        : n(arr.size()), mod(p), tree(n << 2) {
        std::function<void(int,int,int)> build = [&](int now, int l, int r) {
            if (l == r) {
                tree[now].val = arr[l - 1];
                return;
            }
            int mid = l + (r - l) / 2;
            build(now << 1, l, mid);
            build(now << 1 | 1, mid + 1, r);
            pull_up(now);
        };
        build(1, 1, n);
    }
    void add(int l, int r, T val) {
        add(1, 1, n, l, r, val);
    }
    void add(int pos, T val) {
        add(1, 1, n, pos, pos, val);
    }
    T query(int l, int r) {
        return query(1, 1, n, l, r);
    }
};

signed main() {
    freopen("../P3372_8.in", "r", stdin);
    freopen("../P3372_8.txt", "w", stdout);
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, m;
    std::cin >> n >> m;
    std::vector<long long> arr(n);
    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];
    }

    SegmentTree<long long> seg(arr, 8e18);

    for (int i = 1, opt, x, y; i <= m; i++) {
        std::cin >> opt >> x >> y;
        if (opt == 1) {
            long long k;
            std::cin >> k;
            seg.add(x, y, k);
        } else {
            std::cout << seg.query(x, y) << '\n';
        }
    }
}
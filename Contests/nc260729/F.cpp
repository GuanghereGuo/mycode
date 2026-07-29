//
// Created by guanghere on 2026/7/29.
//
#include <bits/stdc++.h>
using namespace std;

class SegmentTree {
    int n, inf;
    vector<int> data;

   public:
    explicit SegmentTree(const int n, const int inf)
        : n(n), inf(inf), data(n * 2, inf) {}

    void clear() {
        fill(data.begin(), data.end(), inf);
    }

    void chmin(int pos, const int value) {
        if (value >= data[pos += n]) {
            return;
        }
        data[pos] = value;
        while (pos > 1) {
            pos >>= 1;
            const auto value = min(data[pos << 1], data[pos << 1 | 1]);
            if (data[pos] == value) {
                break;
            }
            data[pos] = value;
        }
    }

    [[nodiscard]] int query(int l, int r) const {
        auto res = inf;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) {
                res = min(res, data[l++]);
            }
            if (r & 1) {
                res = min(res, data[--r]);
            }
        }
        return res;
    }
};

struct Query {
    int l, r;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    auto a = vector<long long>(n);
    for (auto &x : a) {
        cin >> x;
    }

    auto queries = vector<Query>(q);
    for (auto &[l, r] : queries) {
        cin >> l >> r;
        --l;
        --r;
    }

    auto values = a;
    sort(values.begin(), values.end());
    values.erase(unique(values.begin(), values.end()), values.end());

    auto position = vector<int>(n);
    auto left = vector<int>(n);
    auto right = vector<int>(n);
    for (auto i = 0; i < n; ++i) {
        position[i] =
            lower_bound(values.begin(), values.end(), a[i]) - values.begin();
        left[i] =
            lower_bound(values.begin(), values.end(), 2 * a[i]) -
            values.begin();
        right[i] =
            upper_bound(values.begin(), values.end(), 3 * a[i]) -
            values.begin();
    }

    const auto inf = n + 1;
    auto prev = vector<int>(n);
    auto cur = vector<int>(n);
    auto suffix = vector<int>(n + 1, inf);
    auto answer = vector<int>(q, 1);
    iota(prev.begin(), prev.end(), 0);

    auto seg = SegmentTree(values.size(), inf);
    for (auto len = 2; len <= 60; ++len) {
        seg.clear();
        auto exists = false;

        for (auto i = n - 1; i >= 0; --i) {
            cur[i] = seg.query(left[i], right[i]);
            exists |= cur[i] != inf;
            seg.chmin(position[i], prev[i]);
        }

        if (!exists) {
            break;
        }

        suffix[n] = inf;
        for (auto i = n - 1; i >= 0; --i) {
            suffix[i] = min(cur[i], suffix[i + 1]);
        }
        for (auto i = 0; i < q; ++i) {
            if (suffix[queries[i].l] <= queries[i].r) {
                answer[i] = len;
            }
        }

        swap(prev, cur);
    }

    for (const auto x : answer) {
        cout << x << '\n';
    }
}

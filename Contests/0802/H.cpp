//
// Created by guanghere on 25-8-2.
//
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());

const ll M1 = 1e9 + 7;
const ll M2 = 1e9 + 9;
ll B1, B2;

ll power(ll base, ll exp, ll mod) {
    ll res = 1;
    base %= mod;
    while (exp > 0) {
        if (exp % 2 == 1) res = (res * base) % mod;
        base = (base * base) % mod;
        exp /= 2;
    }
    return res;
}

struct HashValue {
    ll h1 = 0, h2 = 0;

    HashValue() = default;
    HashValue(ll v1, ll v2) : h1(v1), h2(v2) {}

    friend HashValue operator+(const HashValue& a, const HashValue& b) {
        return {(a.h1 + b.h1) % M1, (a.h2 + b.h2) % M2};
    }
    friend HashValue operator*(const HashValue& a, const HashValue& b) {
        return {(a.h1 * b.h1) % M1, (a.h2 * b.h2) % M2};
    }
    bool operator==(const HashValue& other) const {
        return h1 == other.h1 && h2 == other.h2;
    }
};

struct Node {
    HashValue sum_odd, sum_even;
    HashValue lazy;
    Node() : lazy(1, 1) {}
};

vector<ll> a;
vector<Node> tree;
int n;

void push_up(int p) {
    tree[p].sum_odd = tree[p * 2].sum_odd + tree[p * 2 + 1].sum_odd;
    tree[p].sum_even = tree[p * 2].sum_even + tree[p * 2 + 1].sum_even;
}

void apply_lazy(int p, const HashValue& val) {
    tree[p].sum_odd = tree[p].sum_odd * val;
    tree[p].sum_even = tree[p].sum_even * val;
    tree[p].lazy = tree[p].lazy * val;
}

void push_down(int p) {
    if (tree[p].lazy.h1 == 1 && tree[p].lazy.h2 == 1) return;
    apply_lazy(p * 2, tree[p].lazy);
    apply_lazy(p * 2 + 1, tree[p].lazy);
    tree[p].lazy = {1, 1};
}

void build(int p, int l, int r) {
    if (l == r) {
        HashValue h_val = {power(B1, a[l], M1), power(B2, a[l], M2)};
        if (l % 2 != 0) { // 奇数位
            tree[p].sum_odd = h_val;
        } else { // 偶数位
            tree[p].sum_even = h_val;
        }
        return;
    }
    int mid = l + (r - l) / 2;
    build(p * 2, l, mid);
    build(p * 2 + 1, mid + 1, r);
    push_up(p);
}

void update(int p, int l, int r, int ul, int ur, const HashValue& val) {
    if (ul <= l && r <= ur) {
        apply_lazy(p, val);
        return;
    }
    push_down(p);
    int mid = l + (r - l) / 2;
    if (ul <= mid) {
        update(p * 2, l, mid, ul, ur, val);
    }
    if (ur > mid) {
        update(p * 2 + 1, mid + 1, r, ul, ur, val);
    }
    push_up(p);
}

pair<HashValue, HashValue> query(int p, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) {
        return {tree[p].sum_odd, tree[p].sum_even};
    }
    push_down(p);
    int mid = l + (r - l) / 2;
    pair<HashValue, HashValue> res = {{}, {}};
    if (ql <= mid) {
        auto left_res = query(p * 2, l, mid, ql, qr);
        res.first = res.first + left_res.first;
        res.second = res.second + left_res.second;
    }
    if (qr > mid) {
        auto right_res = query(p * 2 + 1, mid + 1, r, ql, qr);
        res.first = res.first + right_res.first;
        res.second = res.second + right_res.second;
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    B1 = rnd() % (M1 - 100) + 50;
    B2 = rnd() % (M2 - 100) + 50;

    int q;
    cin >> n >> q;

    a.resize(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    tree.resize(4 * n + 4);
    build(1, 1, n);

    while (q--) {
        int type;
        cin >> type;
        if (type == 0) {
            int l, r;
            ll v;
            cin >> l >> r >> v;
            HashValue factor = {power(B1, v, M1), power(B2, v, M2)};
            update(1, 1, n, l, r, factor);
        } else {
            int l, r;
            cin >> l >> r;
            auto [odd_sum, even_sum] = query(1, 1, n, l, r);
            if (odd_sum == even_sum) {
                cout << "Yes\n";
            } else {
                cout << "No\n";
            }
        }
    }

    return 0;
}

// //
// // Created by guanghere on 2025/10/7.
// //
// #include <bits/stdc++.h>
//
// class BIT {
//     using ll = long long;
//     int n;
//     std::vector<ll> tr;
//     constexpr static int low_bit(const int x) {
//         return x & -x;
//     }
//
// public:
//     BIT(int nn) : n(nn), tr(nn + 1) {}
//     void add(int idx, ll val) {
//         for (int i = idx; i <= n; i += low_bit(i)) {
//             tr[i] += val;
//         }
//     }
//     ll query(int idx) {
//         ll res = 0;
//         for (int i = idx; i; i -= low_bit(i)) {
//             res += tr[i];
//         }
//         return res;
//     }
// };
//
// int main() {
//     std::ios::sync_with_stdio(false);
//     std::cin.tie(nullptr);
//
//     int ac, ad, n;
//     std::cin >> ac >> ad >> n;
//     const int MAXC = 2000010;
//     BIT bit(MAXC);
//     std::vector<int> a(n), b(n), c(n);
//     for (int i = 0; i < n; ++i) {
//         std::cin >> a[i];
//     }
//     for (int i = 0; i < n; ++i) {
//         std::cin >> b[i];
//     }
//     for (int i = 0; i < n; ++i) {
//         c[i] = std::max(0, a[i] - ac) + std::max(0, b[i] - ad);
//         bit.add(c[i] + 1, 1);
//     }
//
//     int q;
//     std::cin >> q;
//     while (q--) {
//         int k, na, nb;
//         std::cin >> k >> na >> nb;
//         k--;
//         int oldc = c[k];
//         bit.add(oldc + 1, -1);
//         int nc = std::max(0, na - ac) + std::max(0, nb - ad);
//         c[k] = nc;
//         bit.add(nc + 1, 1);
//
//         if (bit.query(1) == 0) {
//             std::cout << 0 << '\n';
//             continue;
//         }
//
//         // bin search for max k st cnt[k-1] >= k
//         int l = 1, r = n + 1;
//         while (l < r) {
//             int mid = (l + r) / 2;
//             if (bit.query(mid) >= mid) {
//                 l = mid + 1;
//             } else {
//                 r = mid;
//             }
//         }
//         std::cout << l - 1 << '\n';
//     }
//     return 0;
// }
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int MAXN = 500010;
ll tree[4 * MAXN];
ll lazy[4 * MAXN];
int NN;

void build(int node, int s, int e) {
    if (s == e) {
        tree[node] = -s;
        return;
    }
    int m = (s + e) / 2;
    build(2 * node, s, m);
    build(2 * node + 1, m + 1, e);
    tree[node] = min(tree[2 * node], tree[2 * node + 1]);
}

void push(int node, int s, int e) {
    if (lazy[node]) {
        tree[node] += lazy[node];
        if (s != e) {
            lazy[2 * node] += lazy[node];
            lazy[2 * node + 1] += lazy[node];
        }
        lazy[node] = 0;
    }
}

void update_range(int node, int s, int e, int l, int r, ll val) {
    push(node, s, e);
    if (s > e || s > r || e < l) return;
    if (l <= s && e <= r) {
        lazy[node] += val;
        push(node, s, e);
        return;
    }
    int m = (s + e) / 2;
    update_range(2 * node, s, m, l, r, val);
    update_range(2 * node + 1, m + 1, e, l, r, val);
    tree[node] = min(tree[2 * node], tree[2 * node + 1]);
}

int get_first(int node, int s, int e) {
    push(node, s, e);
    if (tree[node] > 0) return -1;
    if (s == e) return s;
    int m = (s + e) / 2;
    int left = get_first(2 * node, s, m);
    if (left != -1) return left;
    return get_first(2 * node + 1, m + 1, e);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int ac, dr;
    cin >> ac >> dr;
    int n;
    cin >> n;
    build(1, 0, n);
    vector<int> A(n), D(n);
    for (int i = 0; i < n; ++i)
        cin >> A[i];
    for (int i = 0; i < n; ++i)
        cin >> D[i];
    for (int i = 0; i < n; ++i) {
        int c = max(0, A[i] - ac) + max(0, D[i] - dr);
        if (c <= n) {
            update_range(1, 0, n, c, n, 1);
        }
    }
    int m;
    cin >> m;
    for (int qq = 0; qq < m; ++qq) {
        int k, na, nd;
        cin >> k >> na >> nd;
        k--;
        int oldc = max(0, A[k] - ac) + max(0, D[k] - dr);
        A[k] = na;
        D[k] = nd;
        int newc = max(0, na - ac) + max(0, nd - dr);
        if (oldc <= n) {
            update_range(1, 0, n, oldc, n, -1);
        }
        if (newc <= n) {
            update_range(1, 0, n, newc, n, 1);
        }
        int ans = get_first(1, 0, n);
        cout << ans << '\n';
    }
    return 0;
}
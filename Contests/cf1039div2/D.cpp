#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

using ll = long long;

const int N = 500005;
int p[N];

struct Node {
    ll sum = 0;
    ll min_v = 0, max_v = 0;
    ll lazy_add = 0;
    ll lazy_set = 0;
};

Node tree_f[4 * N], tree_l[2][4 * N];

void push_up(Node tree[], int u) {
    tree[u].sum = tree[2 * u].sum + tree[2 * u + 1].sum;
    tree[u].min_v = min(tree[2 * u].min_v, tree[2 * u + 1].min_v);
    tree[u].max_v = max(tree[2 * u].max_v, tree[2 * u + 1].max_v);
}

void apply_set(Node tree[], int u, int l, int r, ll val) {
    tree[u].sum = (ll)(r - l + 1) * val;
    tree[u].min_v = tree[u].max_v = val;
    tree[u].lazy_set = val;
    tree[u].lazy_add = 0;
}

void apply_add(Node tree[], int u, int l, int r, ll val) {
    tree[u].sum += (ll)(r - l + 1) * val;
    tree[u].min_v += val;
    tree[u].max_v += val;
    tree[u].lazy_add += val;
}

void push_down(Node tree[], int u, int l, int r) {
    int mid = l + (r - l) / 2;
    if (tree[u].lazy_set != 0) {
        apply_set(tree, 2 * u, l, mid, tree[u].lazy_set);
        apply_set(tree, 2 * u + 1, mid + 1, r, tree[u].lazy_set);
        tree[u].lazy_set = 0;
    }
    if (tree[u].lazy_add != 0) {
        apply_add(tree, 2 * u, l, mid, tree[u].lazy_add);
        apply_add(tree, 2 * u + 1, mid + 1, r, tree[u].lazy_add);
        tree[u].lazy_add = 0;
    }
}

void update_point(Node tree[], int u, int l, int r, int pos, ll val) {
    if (l == r) {
        tree[u] = {val, val, val, 0, 0};
        return;
    }
    push_down(tree, u, l, r);
    int mid = l + (r - l) / 2;
    if (pos <= mid) update_point(tree, 2 * u, l, mid, pos, val);
    else update_point(tree, 2 * u + 1, mid + 1, r, pos, val);
    push_up(tree, u);
}

void merge_max(Node tree_dst[], Node tree_src[], int u, int l, int r) {
    if (tree_dst[u].min_v >= tree_src[u].max_v) return;
    if (tree_dst[u].max_v <= tree_src[u].min_v) {
        apply_set(tree_dst, u, l, r, 0);
        tree_dst[u] = tree_src[u];
        return;
    }
    push_down(tree_dst, u, l, r);
    push_down(tree_src, u, l, r);
    int mid = l + (r - l) / 2;
    merge_max(tree_dst, tree_src, 2 * u, l, mid);
    merge_max(tree_dst, tree_src, 2 * u + 1, mid + 1, r);
    push_up(tree_dst, u);
}

void solve() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> p[i];

    for (int i = 0; i < 4 * (n + 1); ++i) {
        tree_f[i] = tree_l[0][i] = tree_l[1][i] = Node();
    }

    ll total_ans = 0;
    int cur = 0, prev = 1;

    for (int i = 1; i <= n; ++i) {
        cur = i % 2;
        prev = (i - 1) % 2;

        // Build L_i
        if (i > 1 && p[i - 1] > p[i]) {
            for(int j=0; j<4*(n+1); ++j) tree_l[cur][j] = tree_l[prev][j];
            apply_add(tree_l[cur], 1, 1, i - 1, 1);
        } else {
            for(int j=0; j<4*(n+1); ++j) tree_l[cur][j] = Node();
        }

        if (i > 2 && p[i - 2] > p[i]) {
            merge_max(tree_l[cur], tree_l[prev], 1, 1, i - 2);
            apply_add(tree_l[cur], 1, 1, i - 2, 1);
        }
        update_point(tree_l[cur], 1, 1, n, i, 1);

        // Build f_i
        merge_max(tree_f, tree_l[cur], 1, 1, i);
        update_point(tree_f, 1, 1, n, i, 1);

        total_ans += tree_f[1].sum;
    }
    cout << total_ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}

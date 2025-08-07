//
// Created by guanghere on 25-8-7.
//
#include <bits/stdc++.h>
using namespace std;

#define int long long

const int mod = 1e9 + 7;

struct Edge {
    int u, v, w;
    bool operator<(const Edge& e) const { return w < e.w; }
};

using pii = pair<int, int>;

struct DSU {
    int n;
    std::vector<int> fa, size;
    DSU(const int _n) : n(_n), fa(_n + 1), size(_n + 1, 1) {
        std::iota(fa.begin(), fa.end(), 0);
    }
    int find(const int x) {
        if (fa[x] == x) return x;
        return fa[x] = find(fa[x]);
    }
    void unite(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) return;
        if (size[x] < size[y]) std::swap(x, y);
        fa[y] = x;
        size[x] += size[y];
    }
};

int mul(int a, int b) { return a % mod * (b % mod) % mod; }

void solve() {
    int n, m, k, cnt = 0, ans = 0, ans1;
    cin >> n >> m >> k;
    vector<Edge> edge;

    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        edge.push_back({u, v, w});
    }
    sort(edge.begin(), edge.end());

    DSU dsu(n), dsu1(n);

    for (const auto& e : edge) {
        if (dsu.find(e.u) != dsu.find(e.v)) {
            dsu.unite(e.u, e.v);
        }
    }

    int x1 = -1, x2 = -1;
    for (int i = 1; i <= n; i++) {
        if (dsu.find(i) == i) {
            if (x1 == -1)
                x1 = i;
            else if (x2 == -1)
                x2 = i;
            cnt++;
        }
    }

    if (n == 0)
        cnt = 0;
    else if (m == 0 && n > 1)
        cnt = n;

    if (cnt > 2) {
        cout << 0 << endl;
    } else if (cnt == 2) {
        cout << mul(mul(k, dsu.size[x1]), dsu.size[x2]) << endl;
    } else {
        cnt = 1, ans1 = n * (n - 1) / 2;

        vector<vector<pii>> mst_adj(n + 1);
        for (const auto& e : edge) {
            int root_u = dsu1.find(e.u);
            int root_v = dsu1.find(e.v);
            if (root_u != root_v) {
                ans = (ans + mul(mul(dsu1.size[root_u], dsu1.size[root_v]),
                                 (e.w - 1 + mod) % mod)) %
                      mod;
                dsu1.unite(e.u, e.v);
                mst_adj[e.u].push_back({e.v, e.w});
                mst_adj[e.v].push_back({e.u, e.w});
            }
        }

        vector<int> depth(n + 1, 0);
        vector<vector<int>> parent(n + 1, vector<int>(20, 0));
        vector<vector<int>> max_w(n + 1, vector<int>(20, 0));

        function<void(int, int, int, int)> dfs_lca = [&](int u, int p, int d,
                                                         int w_to_p) {
            depth[u] = d;
            parent[u][0] = p;
            max_w[u][0] = w_to_p;
            for (int i = 1; i < 20; ++i) {
                parent[u][i] = parent[parent[u][i - 1]][i - 1];
                max_w[u][i] =
                    std::max(max_w[u][i - 1], max_w[parent[u][i - 1]][i - 1]);
            }
            for (auto& edge_pair : mst_adj[u]) {
                int v_node = edge_pair.first;
                int w_val = edge_pair.second;
                if (v_node != p) {
                    dfs_lca(v_node, u, d + 1, w_val);
                }
            }
        };

        if (n > 0) dfs_lca(1, 0, 1, 0);

        auto query_max_w = [&](int u, int v) {
            int res = 0;
            if (depth[u] < depth[v]) swap(u, v);

            for (int i = 19; i >= 0; --i) {
                if (depth[u] - (1 << i) >= depth[v]) {
                    res = std::max(res, max_w[u][i]);
                    u = parent[u][i];
                }
            }

            if (u == v) return res;

            for (int i = 19; i >= 0; --i) {
                if (parent[u][i] != parent[v][i]) {
                    res = std::max(res, std::max(max_w[u][i], max_w[v][i]));
                    u = parent[u][i];
                    v = parent[v][i];
                }
            }
            res = std::max(res, std::max(max_w[u][0], max_w[v][0]));
            return res;
        };

        for (const auto& e : edge) {
            int w_uv = query_max_w(e.u, e.v);
            ans = (ans - ((w_uv - 1 + mod) % mod) + mod) % mod;
        }

        cout << ans << endl;
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}

#include <algorithm>
#include <iostream>
#include <vector>

constexpr int mod = 998244353;
using ll = long long;

#define int long long

struct node {
    int a, b, c;
};

int n, m;
std::vector<std::vector<int>> g, tr;
std::vector<int> map_idx, jc;
std::vector<node> nodes;
std::vector<bool> vis, in_triangle;

int inv(int x) {
    int s = 1, k = mod - 2;
    while (k) {
        if (k & 1) s = s * x % mod;
        x = x * x % mod;
        k >>= 1;
    }
    return s;
}

int C(int x, int y) {
    return jc[x] * inv(jc[y]) % mod * inv(jc[x - y]) % mod;
}

void dfs(int now, int fa, int grandpa) {  // 缩点dfs
    vis[now] = true;
    for (int nxt : g[now]) {
        if (vis[nxt]) {
            if (nxt == grandpa) {
                nodes.push_back({now, fa, grandpa});
            }
            continue;
        }
        dfs(nxt, now, fa);
    }
}

std::vector<int> depth, fa, heavy, top, sz, pos, segtree;
std::vector<int> tri_weight;  // 节点权值（是否为三角节点）
int timer = 0;

void dfs_size(int now, int _fa) {  // First DFS to calculate sizes and heavy child
    sz[now] = 1;
    fa[now] = _fa;
    depth[now] = depth[_fa] + 1;
    int max_size = -1;
    for (int nxt : tr[now]) {
        if (nxt == _fa) continue;
        dfs_size(nxt, now);
        sz[now] += sz[nxt];
        if (sz[nxt] > max_size) {
            max_size = sz[nxt];
            heavy[now] = nxt;
        }
    }
}

void decompose(int now, int h) {  // Second DFS to assign positions and decompose tree into chains
    top[now] = h;
    pos[now] = ++timer;
    if (heavy[now] != -1) {
        decompose(heavy[now], h);  // Continue on heavy chain
    }
    for (int nxt : tr[now]) {
        if (nxt != fa[now] && nxt != heavy[now]) {
            decompose(nxt, nxt);  // Decompose new light chain
        }
    }
}

void build_segtree(int n) {
    segtree.resize(2 * n);
    for (int i = 0; i < n; i++) {
        segtree[n + i] = tri_weight[i + 1];
    }
    for (int i = n - 1; i > 0; --i) {
        segtree[i] = segtree[i * 2] + segtree[i * 2 + 1];
    }
}

int query_segtree(int l, int r, int n) {
    int res = 0;
    for (l += n, r += n; l <= r; l = (l + 1) / 2, r = (r - 1) / 2) {
        if (l & 1) res += segtree[l];
        if (!(r & 1)) res += segtree[r];
    }
    return res;
}

int hld_query(int x, int y, int n) {  // HLD query to count triangle nodes in the path
    int res = 0;
    while (top[x] != top[y]) {
        if (depth[top[x]] > depth[top[y]]) std::swap(x, y);
        res += query_segtree(pos[top[y]], pos[y], n);
        y = fa[top[y]];
    }
    if (depth[x] > depth[y]) std::swap(x, y);
    res += query_segtree(pos[x], pos[y], n);
    return res;
}

int hld_lca(int x, int y) {  // LCA query based on HLD
    while (top[x] != top[y]) {
        if (depth[top[x]] > depth[top[y]]) std::swap(x, y);
        y = fa[top[y]];
    }
    return (depth[x] < depth[y]) ? x : y;
}

signed main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    std::cin >> n >> m;

    g.resize(n + 1);
    in_triangle.resize(n + 1);
    vis.resize(n + 1);
    map_idx.resize(n + 1);

    for (int i = 1, u, v; i <= m; i++) {
        std::cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    dfs(1, 0, -1);  // 初始dfs，缩点

    int nn = n + 1 + nodes.size();
    tr.resize(nn);
    depth.resize(nn);
    fa.resize(nn);
    jc.resize(nn);

    jc[0] = 1;
    for (int i = 1; i < nn; i++) {
        jc[i] = jc[i - 1] * i % mod;
    }

    for (int i = 0; i < nodes.size(); i++) {
        auto &[a, b, c] = nodes[i];
        tr[a].push_back(n + 1 + i);
        tr[b].push_back(n + 1 + i);
        tr[c].push_back(n + 1 + i);
    }

    // 初始化用于树链剖分的数组
    heavy.resize(nn, -1);
    top.resize(nn);
    sz.resize(nn);
    pos.resize(nn);
    depth.resize(nn);
    fa.resize(nn);
    tri_weight.resize(nn, 0);  // 初始化节点权值数组

    // 对于三角形节点，权值设为 1
    for (int i = n + 1; i < nn; i++) {
        tri_weight[i] = 1;
    }

    // 执行树链剖分
    dfs_size(1, 0);   // 计算每个节点的子树大小、重儿子等
    decompose(1, 1);  // 完成树链剖分

    build_segtree(nn);  // 构建线段树

    int q;
    std::cin >> q;

    for (int i = 1; i <= q; i++) {
        int s, f, k;
        std::cin >> s >> f >> k;
        int _lca = hld_lca(s, f);  // 使用树链剖分版LCA
        int dis = depth[s] + depth[f] - 2 * depth[_lca];
        int num_of_triangle = hld_query(s, f, nn);  // 统计路径上的三角节点数
        std::cerr << dis << ' ' << num_of_triangle << '\n';
        if (k < dis || k > dis + num_of_triangle) {
            std::cout << 0 << '\n';
        } else {
            std::cout << C(num_of_triangle, k - dis) << '\n';
        }
    }
}

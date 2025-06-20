//
// Created by 24087 on 24-9-29.
//
#include <algorithm>
#include <iostream>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

constexpr int mod = 998244353, M = 4e5 + 10;

using ll = long long;

#define int long long

struct node {
    int a, b, c;
};

int n, m, tot;
std::vector<std::vector<int>> g, tr;
std::vector<int> map_idx, jc;
std::vector<node> nodes;
std::vector<bool> vis, in_triangle;

int inv(int x) {
    int s = 1, k = mod - 2;
    for (; k; k >>= 1, x = 1ll * x * x % mod) {
        if (k & 1) {
            s = 1ll * s * x % mod;
        }
    }
    return s;
}

int C(int x, int y) {
    return 1ll * jc[x] * inv(jc[y]) % mod * inv(jc[x - y]) % mod;
}

void dfs(int now, int fa, int grandpa) {  // 缩点dfs
    vis[now] = true;
    for (const int nxt : g[now]) {
        if (vis[nxt]) {
            if (nxt == grandpa) {
                nodes.push_back({now, fa, grandpa});
            }
            continue;
        }
        dfs(nxt, now, fa);
    }
}

int nn;
std::vector<int> depth, fa, son, siz, top, dfn;

void get_depth(const int now, int _fa, int dep) {
    depth[now] = dep;
    fa[now] = _fa;
    son[now] = -1;
    siz[now] = 1;
    for (const int nxt : tr[now]) {
        if (depth[nxt]) {
            continue;
        }
        get_depth(nxt, now, dep + 1);
        siz[now] += siz[nxt];
        if (son[now] == -1 || siz[nxt] > siz[son[now]]) {
            son[now] = nxt;
        }
    }
}

void split_tree(const int now, int tp) {
    static int cnt = 0;
    top[now] = tp;
    dfn[now] = ++cnt;
    if (son[now] == -1) {
        return;
    }
    split_tree(son[now], tp);
    for (const int nxt : tr[now]) {
        if (nxt == son[now] || nxt == fa[now]) {
            continue;
        }
        split_tree(nxt, nxt);
    }
}

class BIT {
    static int lowbit(int x) { return x & -x; }
    vector<int> c;
    int n;

   public:
    BIT(int _n) : n(_n), c(_n + 1) {}
    void add(int idx, int val) {
        while (idx <= n) {
            c[idx] += val;
            idx += lowbit(idx);
        }
    }
    int sum(int idx) {
        int ans = 0;
        while (idx > 0) {
            ans += c[idx];
            idx -= lowbit(idx);
        }
        return ans;
    }
    int sum(int l, int r) {
        if(l > r) {
            std::swap(l, r);
        }
        return sum(r) - sum(l - 1);
    }
};

std::unique_ptr<BIT> ptr;

void init_BIT() {
    ptr = std::make_unique<BIT>(nn - 1);
    for (int i = n + 1; i < nn; i++) {
        //std::cerr << dfn[i] << std::endl;
        ptr->add(dfn[i], 1);
    }
}

std::pair<int, int> lca(int x, int y) {  // 返回路径中三角形的数，和lca
    std::vector<bool> vis1(tr.size());
    int ans = 0;
    while (top[x] != top[y]) {
        if (depth[top[x]] < depth[top[y]]) {
            std::swap(x, y);
        }
        ans += ptr->sum(dfn[x], dfn[top[x]]);
        x = fa[top[x]];
    }
    ans += ptr->sum(dfn[x], dfn[y]);
    return {ans, depth[x] < depth[y] ? x : y};
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

    // 读入原图

    dfs(1, 0, -1);

    nn = n + 1 + nodes.size();
    tr.resize(nn);
    depth.resize(nn);
    fa.resize(nn);
    jc.resize(nn);
    son.resize(nn);
    siz.resize(nn);
    top.resize(nn);
    dfn.resize(nn);

    jc[0] = 1;
    for (int i = 1; i < nn; i++) {
        jc[i] = jc[i - 1] * i % mod;
    }

    std::unordered_set<int> st[n + 1 + nodes.size()];
    auto connect = [&](int a, int b) {
        tr[a].push_back(b);
        tr[b].push_back(a);
    };
    auto meet = [&](int a, int b) {
        st[a].emplace(b);
        st[b].emplace(a);
    };
    for (int i = 0; i < nodes.size(); i++) {
        auto &[a, b, c] = nodes[i];
        connect(a, n + 1 + i);
        connect(b, n + 1 + i);
        connect(c, n + 1 + i);
        meet(a, b);
        meet(b, c);
        meet(a, c);
    }  // 建边
    for (int i = 1; i <= n; i++) {
        for (auto j : g[i]) {
            if (st[i].find(j) != st[i].end() || st[j].find(i) != st[j].end()) {
                continue;
            }
            tr[i].push_back(j);
            tr[j].push_back(i);
        }
    }

    for (auto &vec : tr) {
        std::sort(vec.begin(), vec.end());
        vec.erase(std::unique(vec.begin(), vec.end()), vec.end());
    }

    get_depth(1, 0, 1);
    split_tree(1, 1);
    init_BIT();
    //std::cerr << "ok\n";

    // 缩点，并做节点映射，大于n的节点为三角形节点

    int q;
    std::cin >> q;

    for (int i = 1; i <= q; i++) {
        int s, f, k;
        std::cin >> s >> f >> k;
        auto [num_of_triangle, _lca] = lca(s, f);
        int dis = depth[s] + depth[f] - depth[_lca] * 2 - num_of_triangle;
        //std::cerr << _lca << ' ' << num_of_triangle << '\n';
        if (k < dis || k > dis + num_of_triangle) {
            std::cout << 0 << '\n';
            continue;
        } else {
            std::cout << C(num_of_triangle, k - dis) << '\n';
         }
     }
}
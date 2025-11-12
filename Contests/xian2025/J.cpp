//
// Created by guanghere on 2025/11/12.
//
#include <bits/stdc++.h>

#define int long long


class LCA {
    int n, s, log_n;
    std::vector<std::vector<int>> tr, fa;
    std::vector<int> depth;

    void build(int now, int father, int dep) {
        depth[now] = dep;
        fa[now][0] = father;
        for (const int nxt : tr[now]) {
            if (nxt == father) {
                continue;
            }
            build(nxt, now, dep + 1);
        }
    }
public:
    LCA(int n, int s, std::vector<std::vector<int>> tr)
        : n(n),
          s(s),
          log_n(static_cast<int>(std::ceil(std::log2(n)))),
          tr(std::move(tr)),
          fa(n + 1, std::vector<int>(log_n + 1)),
          depth(n + 1) {

        build(s, 0, 1);

        for (int j = 1; j <= log_n; j++) {
            for (int i = 1; i <= n; i++) {
                fa[i][j] = fa[fa[i][j - 1]][j - 1];
            }
        }
    }

    int operator()(int u, int v) {
        if(depth[u] < depth[v])
            std::swap(u, v);
        for(int j = log_n; j >= 0; j--) {
            if(depth[fa[u][j]] >= depth[v])
                u = fa[u][j];
        }
        if(u == v)
            return u;
        for(int j = log_n; j >= 0; j--) {
            if(fa[u][j] != fa[v][j]) {
                u = fa[u][j];
                v = fa[v][j];
            }
        }
        return fa[u][0];
    }
};

void solve() {
    int n, m;
    std::cin >> n >> m;
    std::vector<int> cost(n + 1);
    std::vector<int> cost1(n + 1);
    cost[0] = LLONG_MAX / 2;
    for (int i = 1; i <= n; ++i) {
        std::cin >> cost[i];
    }
    std::vector tr(n + 1, std::vector<int>());
    std::vector<std::pair<int, int>> minc(n + 1, {0, 0});
    std::vector<int> fa(n + 1), dep(n + 1);
    for (int i = 1; i <= n - 1; ++i) {
        int u, v;
        std::cin >> u >> v;
        tr[u].push_back(v);
        tr[v].push_back(u);
    }

    LCA lca(n, 1, tr);

    std::function<void(int, int, int) > dfs = [&](int now, int father, int depth) {
        dep[now] = depth;
        for (auto to : tr[now]) {
            if (to != father) {
                fa[to] = now;
                dfs(to, now, depth + 1);
                if (cost[to] < cost[minc[now].first]) {
                    minc[now].second = minc[now].first;
                    minc[now].first = to;
                } else if (cost[to] < cost[minc[now].second] && to != minc[now].first) {
                    minc[now].second = to;
                }
                cost[now] = std::min(cost[now],cost[minc[now].second] + cost[minc[now].first]);//
            }
        }
    };
    cost1[1]=0;
    std::function<void(int, int) > dfs1 = [&](int now, int father) {
        if (now!=1)cost1[now]=cost1[father]+(minc[father].first==now?cost[minc[father].second]:cost[minc[father].first]);
        for (auto to : tr[now]) {
            if (to != father) {
                dfs1(to, now);
                //
            }
        }
    };
    dfs(1, 0, 1);
    dfs1(1,0);
    // for (int i=1;i<=n;i++) {
    //     std::cout << cost1[i] << " ";
    // }
    for (int i = 1, x, y; i <= m; i++) {
        std::cin >> x >> y;

        int xx = lca(x, y);
        if (y != xx) {
            std::cout << -1 << "\n";
            continue;
        }
        // int now = x, cst = 0;
        // if (dep[now] < dep[y]) {
        //     std::cout << -1 << "\n";
        //     continue;
        // }
        // while (dep[now] >= dep[y]) {
        //     // std::cerr << now << " ";
        //     if (now == y) {
        //         std::cout << cst << "\n";
        //         break;
        //     }
        //     if (dep[now] == dep[y]) {
        //         std::cout << -1 << "\n";
        //         break;
        //     }
        //
        //     cst += (minc[fa[now]].first == now ? cost[minc[fa[now]].second] : cost[minc[fa[now]].first]);
        //     now = fa[now];
        // }
        std::cout<<cost1[x]-cost1[y]<<std::endl;
    }
}

signed main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int t;
    std::cin >> t;

    while (t--) {
        solve();
    }
}
/*

1

3 6

1 1 1

1 2

1 3

2 3

1 2

2

1

3 2

1 3

3 1
 */
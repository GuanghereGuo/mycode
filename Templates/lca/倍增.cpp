//
// Created by 24087 on 24-10-11.
//
#include <cmath>
#include <iostream>
#include <vector>

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
    LCA(int n, int s, std::vector<std::vector<int>> &&tr)
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

int main() {
    int n, m, s;
    std::cin >> n >> m >> s;
    std::vector<std::vector<int>> tr(n + 1);

    for (int i = 1, u, v; i <= n - 1; i++) {
        std::cin >> u >> v;
        tr[u].push_back(v);
        tr[v].push_back(u);
    }

    LCA lca(n, s, std::move(tr));

    for (int i = 1, u, v; i <= m; i++) {
        std::cin >> u >> v;
        std::cout << lca(u, v) << '\n';
    }
}
//
// Created by 24087 on 24-10-12.
//
#include <iostream>
#include <vector>

class LCA {
    int n, s;
    std::vector<std::vector<int>> tr;
    std::vector<int> fa, siz, dep, son, top, dfn;

    void dfs1(int now, int father, int depth) {
        fa[now] = father;
        dep[now] = depth;
        siz[now] = 1;
        son[now] = 0;
        for(int nxt : tr[now]) {
            if(nxt == father) {
                continue;
            }
            dfs1(nxt, now, depth + 1);
            siz[now] += siz[nxt];
            if(siz[nxt] > siz[son[now]]) {
                son[now] = nxt;
            }
        }
    }
    void dfs2(int now, int tp) {
        static int  tot = 0;
        top[now] = tp;
        dfn[now] = ++tot;
        if(son[now] == 0)
            return;
        dfs2(son[now], tp);
        for(int nxt : tr[now]) {
            if(nxt == son[now] || nxt == fa[now])
                continue;
            dfs2(nxt, nxt);
        }
    }

   public:
    LCA(int n, int s, std::vector<std::vector<int>> &&tr)
        : n(n),
          s(s),
          tr(std::move(tr)),
          fa(n + 1),
          siz(n + 1),
          dep(n + 1),
          son(n + 1),
          top(n + 1),
          dfn(n + 1) {

        dfs1(s, 0, 1);
        dfs2(s, s);
    }

    int operator()(int u, int v) {
        while(top[u] != top[v]) {
            if(dep[top[u]] > dep[top[v]]) {
                u = fa[top[u]];
            } else {
                v = fa[top[v]];
            }
        }
        return dep[u] < dep[v] ? u : v;
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
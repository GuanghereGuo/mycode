//
// Created by 24087 on 24-10-11.
//
#include <iostream>
#include <numeric>
#include <utility>
#include <vector>

class DisjointSetUnion {
    std::vector<int> fa, siz;

   public:
    explicit DisjointSetUnion(const int n) : fa(n + 1), siz(n + 1, 1) {
        std::iota(fa.begin(), fa.end(), 0);
    }

    int find(const int x) {
        if (fa[x] == x) return x;
        return fa[x] = find(fa[x]);
    }

    void merge(int x, int y) {//不能优化
        x = find(x);
        y = find(y);
        if (x == y) return;
        fa[y] = x;
    }
};

class LCA {
    int n, m, s;
    std::vector<std::vector<int>> tr;
    std::vector<std::vector<std::pair<int, int>>> qes;
    std::vector<bool> vis;
    std::vector<int> ans;
    DisjointSetUnion dsu;

    void dfs(int now) {
        vis[now] = true;
        for(int nxt : tr[now]) {
            if(vis[nxt]) {
                continue;
            }
            dfs(nxt);
            dsu.merge(now, nxt);
        }
        for(auto [i, id] : qes[now]) {
            if(vis[i]) {
                ans[id] = dsu.find(i);
            }
        }
    }

   public:
    LCA(int n, int m, int s, std::vector<std::vector<int>> &&tr,
        std::vector<std::vector<std::pair<int, int>>> &&qes)
        : n(n), m(m), s(s), tr(std::move(tr)), qes(std::move(qes)), vis(n + 1), ans(m), dsu(n) {}
    std::vector<int> get_ans() {
        dfs(s);
        return ans;
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

    std::vector<std::vector<std::pair<int, int>>> qes(n + 1);

    for(int i = 0, u, v; i < m; i++) {
        std::cin >> u >> v;
        qes[u].emplace_back(v, i);
        qes[v].emplace_back(u, i);
    }

    LCA lca(n, m, s, std::move(tr), std::move(qes));

    auto ans = lca.get_ans();

    for(int i : ans) {
        std::cout << i << '\n';
    }
}
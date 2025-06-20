//
// Created by guanghere on 25-3-12.
//
#include <iostream>
#include <vector>

class Tarjan {
    int n, timestamp = 0, cnt = 0;
    std::vector<std::vector<int>> g, sccs;
    std::vector<bool> in_stack;
    std::vector<int> low, dfn, color, stk{};

    void dfs(int now) {
        low[now] = dfn[now] = ++timestamp;
        in_stack[now] = true;
        stk.push_back(now);
        for (auto v : g[now]) {
            if (!dfn[v]) {
                dfs(v);
                low[now] = std::min(low[now], low[v]);
            } else if (in_stack[v]) {
                low[now] = std::min(low[now], dfn[v]);
            }
        }
        if (low[now] == dfn[now]) {
            int tmp;
            cnt++;
            std::vector<int> scc;
            do {
                tmp = stk.back();
                stk.pop_back();
                in_stack[tmp] = false;
                color[tmp] = cnt;
                scc.push_back(tmp);
            } while (tmp != now);
            sccs.emplace_back(std::move(scc));
        }
    }

   public:
    Tarjan(int n)
        : n(n),
          g(n + 1, std::vector<int>()),
          sccs(1),
          in_stack(n + 1),
          low(n + 1),
          dfn(n + 1),
          color(n + 1) {}
    void add_edge(int u, int v) { g[u].push_back(v); }
    void run() {
        for (int i = 1; i <= n; i++) {
            if (!dfn[i]) {
                dfs(i);
            }
        }
    }
    int get_cnt() { return cnt; }
    const auto& get_sccs() { return sccs; }
    const auto& get_color() { return color; }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, m;
    std::cin >> n >> m;
    Tarjan tarjan(n);

    for (int i = 0, u, v; i < m; i++) {
        std::cin >> u >> v;
        tarjan.add_edge(u, v);
    }

    tarjan.run();
    int cnt = tarjan.get_cnt();
    const auto &sccs = tarjan.get_sccs();
    for (auto &scc : sccs) {
        if (scc.size() == 1) {
            cnt--;
        }
    }
    std::cout << cnt << '\n';
}
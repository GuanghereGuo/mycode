//
// Created by guanghere on 25-3-12.
//
#include <iostream>
#include <queue>
#include <unordered_set>
#include <vector>

class Tarjan {
    int n, timestamp = 0, cnt = 0;
    std::vector<std::vector<int>> g, sccs;
    std::vector<bool> in_stack;
    std::vector<int> low, dfn, color, stk{};
    std::vector<std::vector<int>> reduced{};

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

    void reduce() {
        std::vector<std::unordered_set<int>> tmp(cnt + 1);
        for (int i = 1; i <= n; i++) {
            for (auto v : g[i]) {
                int uid = color[i];
                int vid = color[v];
                if (uid != vid) {
                    tmp[uid].insert(vid);
                }
            }
        }
        reduced.resize(cnt + 1);
        for (int i = 1; i <= cnt; i++) {
            reduced[i] = std::vector<int>(tmp[i].begin(), tmp[i].end());
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
        reduce();
    }
    int get_cnt() { return cnt; }
    const auto& get_sccs() { return sccs; }
    const auto& get_color() { return color; }
    const auto& get_reduced() { return reduced; }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, m;
    std::cin >> n >> m;
    Tarjan tarjan(n);

    std::vector<int> val(n + 1);
    for (int i = 1; i <= n; i++) {
        std::cin >> val[i];
    }

    for (int i = 0, u, v; i < m; i++) {
        std::cin >> u >> v;
        tarjan.add_edge(u, v);
    }
    tarjan.run();

    const int cnt = tarjan.get_cnt();
    const auto &sccs = tarjan.get_sccs();
    const auto &color = tarjan.get_color();
    const auto g = tarjan.get_reduced();
    //std::cerr << cnt << std::endl;

    //topo
    std::vector<int> in_degree(cnt + 1), dp(cnt + 1), sum(cnt + 1);
    std::queue<int> q;
    for (int i = 1; i <= cnt; i++) {
        for (auto v : g[i]) {
            in_degree[v]++;
        }
    }
    for (int i = 1; i <= cnt; i++) {
        for (const auto now : sccs[i]) {
            sum[i] += val[now];
        }
        if (in_degree[i] == 0) {
            q.push(i);
            dp[i] = sum[i];
        }
    }

    while (!q.empty()) {
        int now = q.front();
        q.pop();
        for (auto v : g[now]) {
            in_degree[v]--;
            dp[v] = std::max(dp[v], dp[now] + sum[v]);
            if (in_degree[v] == 0) {
                q.push(v);
            }
        }
    }
    int ans = 0;
    for (int i = 1; i <= cnt; i++) {
        ans = std::max(ans, dp[i]);
    }
    std::cout << ans << '\n';
}
//
// Created by 24087 on 24-9-28.
//
#include <iostream>
#include <vector>
#include <functional>

#define int long long

struct edge {
    int to, val;
};

signed main() {
    int n, m;
    std::cin >> n >> m;

    std::vector<std::vector<edge>> g(n + 1);
    std::vector<bool> vis(n + 1);

    for (int i = 1; i <= m; i++) {
        int u, v, val;
        std::cin >> u >> v >> val;
        g[u].push_back({v, val});
        g[v].push_back({u, val});
    }

    int ans = 0;

    std::function<void(int, int, int)> dfs = [&](int now, int dep, int sum) {
        if(dep == n) {
            ans = std::max(ans, sum);
            return;
        }
        for(auto [to, val] : g[now]) {
            if(vis[to])
                continue;
            vis[to] = true;
            dfs(to, dep + 1, sum + val);
            vis[to] = false;
        }
    };

    for(int i = 1; i <= n; i++) {
        vis[i] = true;
        dfs(i, 1, 0);
        vis[i] = false;
    }

    std::cout << ans;
}
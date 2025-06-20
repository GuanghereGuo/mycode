//
// Created by 24087 on 24-11-5.
//
#include <iostream>
#include <numeric>
#include <queue>
#include <vector>

int n, m, k;
std::vector<std::vector<int>> g;

std::vector<std::vector<int>> tmp;
std::vector<bool> vis;
void dfs(int now, int dep) {
    vis[now] = true;
    for (auto &v : g[now]) {
        if (vis[v]) continue;
        tmp[now].push_back(v);
        dfs(v, dep + 1);
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    std::cin >> n >> m >> k;

    g.resize(n + 1);  // u->v表示u能够邀请v
    tmp.resize(n + 1);
    vis.resize(n + 1);

    std::vector<bool> busy(n + 1);
    for (int i = 1, pos; i <= k; i++) {
        std::cin >> pos;
        busy[pos] = true;
    }  // 如果busy[i]为true，g[i] = {}

    for (int i = 1, u, v; i <= m; i++) {
        std::cin >> u >> v;
        if (!busy[u]) {
            g[u].push_back(v);
        }
        if (!busy[v]) {
            g[v].push_back(u);
        }
    }

    for (int i = 1; i <= n; i++) {
        if (!busy[i]) {
            dfs(i, 1);
            if (std::accumulate(vis.begin(), vis.end(), 0) == n) {
                std::cout << "Yes\n"
                          << std::accumulate(
                                 tmp.begin(), tmp.end(), 0,
                                 [](int sum, const std::vector<int> &v) {
                                     return sum + !v.empty();
                                 })
                          << '\n';
                std::queue<int> q;
                q.push(i);
                while (!q.empty()) {
                    int now = q.front();
                    q.pop();
                    if (tmp[now].empty()) {
                        continue;
                    }
                    std::cout << now << ' ' << tmp[now].size() << ' ';
                    for (auto &v : tmp[now]) {
                        std::cout << v << ' ';
                        q.push(v);
                    }
                    std::cout << '\n';
                }
            } else {
                std::cout << "No\n";
            }
            std::cout << std::flush;
            return 0;
        }
    }
    std::cout << "No\n";
}
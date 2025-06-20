//
// Created by 24087 on 9/21/2024.
//
#include <climits>
#include <iostream>
#include <queue>
#include <vector>

struct edge {
    int to, val;
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, m, s;
    std::cin >> n >> m >> s;

    std::vector graph(n + 1, std::vector<edge>());
    std::vector<int> dis(n + 1, INT_MAX);
    std::vector<bool> vis(n + 1);

    for (int i = 1; i <= m; i++) {
        int u, v, w;
        std::cin >> u >> v >> w;
        graph[u].push_back({v, w});
    }

    std::deque<int> q;
    dis[s] = 0;
    vis[s] = true;
    q.push_back(s);

    while (!q.empty()) {
        const int now = q.front();
        q.pop_front();
        vis[now] = false;


        for (auto [to, val]: graph[now]) {
            if (dis[to] > static_cast<long long>(dis[now]) + val) {
                dis[to] = dis[now] + val;
                if(!vis[to]) {
                    q.push_back(to);
                    vis[to] = true;
                }
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        std::cout << dis[i] << ' ';
    }
}

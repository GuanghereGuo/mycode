//
// Created by 24087 on 9/19/2024.
//
#include <climits>
#include <iostream>
#include <queue>
#include <vector>

struct edge {
    int to, val;
};
struct node {
    int idx, m_dis;
    // node(int _i, int _d) : idx(_i), m_dis(_d) {}
    friend bool operator<(const node &a, const node &b) { return a.m_dis > b.m_dis; }
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

    std::priority_queue<node> q;
    dis[s] = 0;

    q.push({s, 0});

    while (!q.empty()) {
        const int now = q.top().idx;
        q.pop();
        if (vis[now])
            continue;
        vis[now] = true;
        for (auto [to, val]: graph[now]) {
            if (vis[to])
                continue;
            if (dis[to] > static_cast<long long>(dis[now]) + val) {
                dis[to] = dis[now] + val;
                q.push({to, dis[to]});
                // vis[to] = true; !!!!NO!!!!!!
            }
        }
    }


    for (int i = 1; i <= n; i++) {
        std::cout << dis[i] << ' ';
    }
}

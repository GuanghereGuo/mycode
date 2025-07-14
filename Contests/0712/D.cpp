//
// Created by guanghere on 25-7-12.
//
#include <climits>
#include <iostream>
#include <queue>
#include <vector>

#define int long long

struct edge {
    int to, val;
};
struct node {
    int idx, m_dis;
    // node(int _i, int _d) : idx(_i), m_dis(_d) {}
    friend bool operator<(const node &a, const node &b) { return a.m_dis > b.m_dis; }
};

signed main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, m, s = 1;
    std::cin >> n >> m;

    std::vector graph(n + 1, std::vector<edge>());
    std::vector<int> dis(n + 1, LLONG_MAX), g(n + 1), r(n + 1);
    std::vector<bool> vis(n + 1);

    for (int i = 1; i <= n; i++) {
        std::cin >> r[i] >> g[i];
    }

    for (int i = 1; i <= m; i++) {
        int u, v, w;
        std::cin >> u >> v >> w;
        graph[u].push_back({v, w});
        graph[v].push_back({u, w});
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
            int time = val;
            if (dis[now] % (r[now] + g[now]) >= r[now]) {
                time += r[now] + g[now] - dis[now] % (r[now] + g[now]);
            }
            if (dis[to] > dis[now] + time) {
                dis[to] = dis[now] + time;
                q.push({to, dis[to]});
            }
        }
    }

    std::cout << dis[n] << '\n';
}

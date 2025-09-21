//
// Created by guanghere on 25-9-7.
//
#include <bits/stdc++.h>

#define int long long

struct edge
{
    int to = 0, val = 0;
};
struct node
{
    int idx;
    std::pair<int, int> dis;
    bool operator<(const node& x) const
    {
        return dis > x.dis;
    }
};

int n, m, V, T;
std::vector<std::vector<edge>> g;

auto Dijkstra(const std::vector<std::vector<edge>> &g)
{
    int s = T;
    std::priority_queue<node> q;
    std::vector dis(n + 1, std::make_pair<int, int>(LLONG_MAX / 4, 0));
    std::vector<bool> vis(n + 1);
    dis[s] = std::make_pair<int, int>(0, 0);
    q.emplace(T, std::make_pair<int, int>(0, 0));

    while (!q.empty())
    {
        const int now = q.top().idx;
        q.pop();
        if (vis[now])
            continue;
        vis[now] = true;

        auto add = [](std::pair<int, int> a, int b)
        {
            a.second += b;
            if (a.second > V)
            {
                a.first++;
                a.second = b;
            }
            return a;
        };
        for (auto [to, val] : g[now])
        {
            if (vis[to])
                continue;
            if (dis[to] > add(dis[now] ,val))
            {
                dis[to] = add(dis[now] ,val);
                q.emplace(to, dis[to]);
            }
        }
    }
    return dis;
}


signed main()
{
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    std::ios::sync_with_stdio(false);

    std::cin >> n >> m >> V >> T;
    g.resize(n + 1);
    for (int i = 1, u, v, w; i <= m; i++)
    {
        std::cin >> u >> v >> w;
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
    }

    auto dis = Dijkstra(g);

    for (int i = 1; i <= n; i++)
    {
        // std::cerr << dis[i].first << ' ' << dis[i].second << '\n';
        if (i == T)
        {
            std::cout << 1 << ' ';
            continue;
        }
        int ans = dis[i].first + static_cast<long long>(dis[i].second != 0);
        std::cout << (dis[i].first == LLONG_MAX / 4 ? -1 : ans) << ' ';
    }

}
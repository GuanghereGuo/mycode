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
    int idx, dis;
    bool operator<(const node& x) const
    {
        return dis > x.dis;
    }
};

int n, m;
std::vector<std::vector<edge>> g;
std::vector<int> fa, dis;
std::vector<std::pair<int, int>> tele;

std::vector<int> Dijkstra(const std::vector<std::vector<edge>> &g)
{
    constexpr int s = 0;
    std::priority_queue<node> q;
    std::vector<int> dis(n + 1, LLONG_MAX);
    std::vector<bool> vis(n + 1);
    dis[s] = 0;
    q.emplace(0, 0);

    while (!q.empty())
    {
        const int now = q.top().idx;
        q.pop();
        if (vis[now])
            continue;
        vis[now] = true;
        for (auto [to, val] : g[now])
        {
            if (vis[to])
                continue;
            if (dis[to] > (long long)dis[now] + val)
            {
                dis[to] = dis[now] + val;
                q.emplace(to, dis[to]);
            }
        }
    }
    return dis;
}

void dfs(int now)
{
    for (auto &[nxt, val] : g[now])
    {
        // std::cerr << nxt << ' ' << val << '\n';
        if (nxt == fa[now])
            continue;
        dis[nxt] = dis[now] + val;
        fa[nxt] = now;
        dfs(nxt);
    }
}

signed main()
{
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    std::ios::sync_with_stdio(false);

    std::cin >> n >> m;
    g.resize(n + 1);
    fa.resize(n + 1);
    dis.resize(n + 1);
    for (int i = 1, u, v, w; i <= n - 1; i++)
    {
        std::cin >> u >> v >> w;
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
    }
    for (int i = 1, u, v; i <= m; i++)
    {
        std::cin >> u >> v;
        tele.emplace_back(u, v);
    }
    dfs(1);

    for (int j = 0; j <= n; j++)
    {
        int ans = 0;
        for (int i = 1; i <= n; i++)
        {
            ans += dis[i];
        }
        std::cout << ans << '\n';
        if (j != n)
        {
            for (auto [u, v] : tele)
            {
                // tr[0].emplace_back(u, dis[v]);
                // tr[0].emplace_back(v, dis[u]);
                if (dis[u] < dis[v])
                {
                    g[0].emplace_back(v, dis[u]);
                } else
                {
                    g[0].emplace_back(u, dis[v]);
                }
            }
            for (int i = 1; i <= n; i++)
            {
                g[0].emplace_back(i, dis[i]);
            }

            dis = Dijkstra(g);
            g[0].clear();
        }
    }
}
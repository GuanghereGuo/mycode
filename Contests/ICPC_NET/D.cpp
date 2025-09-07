//
// Created by guanghere on 25-9-7.
//
#include <bits/stdc++.h>
#define int long long

using namespace std;

int n, fa[static_cast<long long>(1e6)], maxgr[static_cast<long long>(1e6)], mingr[static_cast<long long>(1e6)], vis[
        static_cast<long long>(1e6)];


int find(int x)
{
    if (fa[x] == x)return x;
    return find(fa[x]);
}

signed main()
{
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> n;
    vector<int> weight(n);
    vector<pair<int,int>> edge(n - 1);
    priority_queue<pair<int,int>> var;

    for (int i = 0; i < n; i++)
    {
        cin >> weight[i];
        fa[i] = i;
        maxgr[i] = LLONG_MIN, mingr[i] = LLONG_MAX;
    }
    for (int i = 0; i < n - 1; i++)
    {
        int tmpx, tmpy;
        cin >> tmpx >> tmpy;
        edge[i] = make_pair(tmpx - 1, tmpy - 1);
        var.emplace(abs(weight[tmpx - 1] - weight[tmpy - 1]), i);
    }
    int ans = 0;
    while (var.size())
    {
        auto svar = var.top();
        var.pop();
        int u = edge[svar.second].first, v = edge[svar.second].second, wei = svar.first;
        if (vis[u] == 0 and vis[v] == 0) //新双节点
        {
            vis[u] = vis[v] = 1;
            fa[u] = find(v);
            maxgr[v] = max(weight[u], weight[v]);
            mingr[v] = min(weight[u], weight[v]);
            ans += wei;
        }
        else if (find(u) != u and vis[v] == 0 and find(v) == v)
        {
            if (weight[v] < mingr[find(u)])
            {
                vis[v] = 1;
                ans -= maxgr[find(u)] - mingr[find(u)];
                mingr[find(u)] = weight[v];
                ans += maxgr[find(u)] - mingr[find(u)];
                fa[v] = find(u);
            }
            else if (weight[v] > maxgr[find(u)])
            {
                vis[v] = 1;
                ans -= maxgr[find(u)] - mingr[find(u)];
                maxgr[find(u)] = weight[v];
                ans += maxgr[find(u)] - mingr[find(u)];
                fa[v] = find(u);
            }
        }
        else if (find(u) == u and vis[u] == 0 and find(v) != v)
        {
            if (weight[u] < mingr[find(v)])
            {
                vis[u] = 1;
                ans -= maxgr[find(v)] - mingr[find(v)];
                mingr[find(v)] = weight[u];
                ans += maxgr[find(v)] - mingr[find(v)];
                fa[u] = find(v);
            }
            else if (weight[u] > maxgr[find(v)])
            {
                vis[u] = 1;
                ans -= maxgr[find(v)] - mingr[find(v)];
                maxgr[find(v)] = weight[u];
                ans += maxgr[find(v)] - mingr[find(v)];
                fa[u] = find(v);
            }
        }
        else
        {
            int org = maxgr[find(u)] - mingr[find(u)] + maxgr[find(v)] - mingr[find(v)];
            // ans -= maxgr[find(u)]-mingr[find(u)];
            // ans -= maxgr[find(v)]-mingr[find(v)];
            int nmax = max(maxgr[find(u)], maxgr[find(v)]);
            int nmin = max(mingr[find(u)], mingr[find(v)]);
            int nans = nmax - nmin;
            if (org < nans)
            {
                ans -= org;
                ans += nans;
                maxgr[find(u)] = max(maxgr[find(u)], maxgr[find(v)]);
                mingr[find(u)] = min(mingr[find(u)], mingr[find(v)]);
                fa[find(v)] = find(u);
            }
        }
    }
    cout << ans;
}

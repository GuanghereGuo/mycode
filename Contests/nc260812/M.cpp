// 作者: Alencryenfo
// 日期: 2026-08-12 15:02:19
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, m;
    cin >> n >> m;

    vector<array<int, 26>> tr(1);
    tr[0].fill(-1);
    vector<int> fa(1, -1), pth, st(n + 1);

    for (int i = 0; i < n; i++)
    {
        string s;
        cin >> s;
        st[i] = pth.size();
        int u = 0;
        for (auto cha : s)
        {
            int x = cha - 'a';
            if (tr[u][x] == -1)
            {
                tr[u][x] = tr.size();
                array<int, 26> a;
                a.fill(-1);
                tr.push_back(a);
                fa.push_back(u);
            }
            u = tr[u][x];
            pth.push_back(u);
        }
    }
    st[n] = pth.size();
    int V = tr.size(), L = pth.size();
    vector<int> nx(L), last(V, INT_MAX);
    for (int i = n - 1; i >= 0; i--)
    {
        for (int j = st[i]; j < st[i + 1]; j++)
        {
            int v = pth[j];
            nx[j] = last[v];
            last[v] = i;
        }
    }
    vector<char> in(V);
    vector<int> son(V), nxt(V, INT_MAX);
    priority_queue<pair<int, int>> q;

    ll ans = 0, cnt = 0;
    auto push = [&](int v)
    {
        if (v and in[v] and son[v] == 0)
            q.push(make_pair(nxt[v], v));
    };

    for (int i = 0; i < n; i++)
    {
        for (int j = st[i]; j < st[i + 1]; j++)
        {
            int v = pth[j];
            if (!in[v])
            {
                in[v] = 1;
                cnt++;
                ans++;
                if (fa[v])
                    son[fa[v]]++;
            }
        }
        for (int j = st[i]; j < st[i + 1]; j++)
        {
            nxt[pth[j]] = nx[j];
        }
        push(pth[st[i + 1] - 1]);
        while (cnt > m)
        {
            while (true)
            {
                auto [t, v] = q.top();
                if (!in[v] or son[v] or nxt[v] != t)
                {
                    q.pop();
                }
                else
                    break;
            }
            auto [t, v] = q.top();
            q.pop();
            in[v] = 0;
            cnt--;
            int p = fa[v];
            if (p)
            {
                son[p]--;

                if (son[p] == 0)
                    push(p);
            }
        }
    }
    cout << ans << "\n";
    return 0;
}
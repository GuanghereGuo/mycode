//
// Created by guanghere on 25-9-7.
//
#include <bits/stdc++.h>

int main()
{
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);
    int m, n;
    std::cin >> n >> m;
    std::vector<std::pair<int, int>> prs(m + 1);
    for (int i = 1; i <= m; i++)
    {
        std::cin >> prs[i].first >> prs[i].second;
    }
    std::sort(prs.begin() + 1, prs.end());
    std::pair<int, int> pr(1, 2);
    for (int i = 1; i <= m; i++)
    {
        if (pr == prs[i])
        {
            pr.first++;
            pr.second++;
        }
    }
    if (pr.second == n + 1)
    {
        std::cout << "Yes\n";
    } else
    {
        std::cout << "No\n";
    }
}
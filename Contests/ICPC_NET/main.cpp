//
// Created by guanghere on 25-9-7.
//
#include <bits/stdc++.h>

int main()
{
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);
    int n, k;
    std::cin >> n >> k;
    std::vector<bool> vec(n + 1, true);
    for (int i = 1, x; i <= k; i++)
    {
        std::cin >> x;
        vec[x] = false;
    }
    long long ans = 0;
    for (int i = 1; i <= n; i++)
    {
        if (vec[i])
            continue;
        for (int j = i + 1; j <= n; j++)
        {
            if (vec[j])
                continue;
            ans += std::gcd(n, j - i);
        }
    }
    std::cout << ans;
}
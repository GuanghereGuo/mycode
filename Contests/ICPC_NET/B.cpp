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
    for (int i = 1; i <= k / 2; i++)
    {
        std::cout << i << ' ';
    }
    for (int i = n - (k / 2 + (k & 1)) + 1; i <= n; i++)
    {
        std::cout << i << ' ';
    }
}
//
// Created by guanghere on 2025/10/12.
//
#include <bits/stdc++.h>

int a[100][100] = {0};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            std::cin >> a[i][j];
        }
    }
    std::set<int> sum;
    for (int i = 1; i <= n - 1; ++i) {
        for (int j = 1; j <= m - 1; ++j) {
            int s1 = a[i][j] + a[i][j + 1];
            int s2 = a[i + 1][j] + a[i + 1][j];
            if (!sum.count(s1) && !sum.count(s2)) {
                sum.insert(s1);
                sum.insert(s2);
            } else {
                std::cout << "no\n";
                return 0;
            }
        }
    }
    std::cout << "yes\n";
}
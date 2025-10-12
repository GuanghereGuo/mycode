//
// Created by guanghere on 2025/10/12.
//
#include <bits/stdc++.h>

void solve() {
    int n, m;
    std::cin >> n >> m;
    int cnt = 0;
    std::vector g(n + 1, std::vector<int>(m + 1));
    for (int i = 2; i <= n + m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (i - j < 1 || i - j > m)
                continue;
            g[j][i - j] = ++cnt;
        }
    }
    std::cout << "yes\n";
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            std::cout << g[i][j] << " ";
        }
        std::cout << '\n';
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }
}
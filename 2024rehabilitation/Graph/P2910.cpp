//
// Created by 24087 on 9/19/2024.
//
#include <climits>
#include <iostream>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, m;
    std::cin >> n >> m;

    std::vector graph(n + 1, std::vector<int>(n + 1));
    std::vector<int> vec(m + 1);

    for (int i = 1; i <= m; i++) {
        std::cin >> vec[i];
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++)
            std::cin >> graph[i][j];
    }

    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                graph[i][j] = static_cast<int>(std::min(static_cast<long long>(graph[i][j]),
                                                        static_cast<long long>(graph[i][k]) + graph[k][j]));
            }
        }
    }

    int ans = 0;

    for (int i = 1; i <= m - 1; i++) {
        ans += graph[vec[i]][vec[i + 1]];
    }
    std::cout << ans;
}

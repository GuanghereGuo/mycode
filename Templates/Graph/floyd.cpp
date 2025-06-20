//
// Created by 24087 on 9/19/2024.
//
#include <climits>
#include <iostream>
#include <vector>

int main() {
    int n, m, s;
    std::cin >> n >> m >> s;

    std::vector graph(n + 1, std::vector<long long>(n + 1, INT_MAX));

    for (int i = 1; i <= m; i++) {
        long long u, v, w;
        std::cin >> u >> v >> w;
        graph[u][v] = std::min(graph[u][v], w);//神金，有重边
    }
    for (int i = 1; i <= n; i++) {
        graph[i][i] = 0;
    }

    for (int k = 1; k <= n; k++) {
        for (int x = 1; x <= n; x++) {
            for (int y = 1; y <= n; y++) {
                graph[x][y] = std::min(graph[x][y], graph[x][k] + graph[k][y]);
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        std::cout << graph[s][i] << ' ';
    }
}

//
// Created by guanghere on 25-3-23.
//
#include <iostream>
#include <limits>
#include <queue>
#include <vector>
#include <algorithm>

using ull = unsigned long long;

struct Edge {
    int to, val;
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int t = 1;
    std::cin >> t;
    while (t--) {
        int n, m;
        std::cin >> n >> m;
        std::vector<std::vector<Edge>> g(n + 1), rev(n + 1);
        int rev_u = 0, rev_v = 0;
        for (int i = 1, u, v, w; i <= m; i++) {
            std::cin >> u >> v >> w;
            if (u < v) {
                g[u].push_back({v, w});
                rev[v].push_back({u, w});
            } else {
                rev_u = u; rev_v = v;
            }
        }
        for (int i = 1; i <= n; i++) {

        }
    }
}
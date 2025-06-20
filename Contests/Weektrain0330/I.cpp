//
// Created by guanghere on 25-3-30.
//
#include <iostream>
#include <queue>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<std::vector<int>> graph(n + 1);
    std::vector<int> ind(n + 1, 0);
    std::queue<int> q;

    for (int i = 1, m; i <= n; i++) {
        std::cin >> ind[i];
        if (ind[i] == 0) {
            q.push(i);
        }
        for (int j = 1, u; j <= ind[i]; j++) {
            std::cin >> u;
            graph[u].push_back(i);
        }
    }

    if (q.size() != 1) {
        std::cout << 0 << "\n";
        return 0;
    }
    bool flag = true;
    //topological sort
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        flag = false;
        for (int v : graph[u]) {
            ind[v]--;
            if (ind[v] == 0) {
                if (flag) {
                    std::cout << 0 << "\n";
                    return 0;
                }
                flag = true;
                q.push(v);
            }
        }
    }
    std::cout << 1 << "\n";
}
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

constexpr int MAXN = 105;

std::vector<int> graph[MAXN];
int inDegree[MAXN];
int dp[MAXN];

void topoSort(int n) {
    std::queue<int> q;
    for (int i = 1; i <= n; ++i) {
        if (inDegree[i] == 0) {
            q.push(i);
        }
    }

    while (!q.empty()) {
        int node = q.front();
        q.pop();
        
        for (int neighbor : graph[node]) {
            dp[neighbor] = std::max(dp[neighbor], dp[node] + 1);
            if (--inDegree[neighbor] == 0) {
                q.push(neighbor);
            }
        }
    }
}

int main() {
    int n, m;
    std::cin >> n >> m;

    for (int i = 0; i < m; i++) {
        int u, v;
        std::cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
        inDegree[v]++;
        inDegree[u]++;
    }

    for (int i = 1; i <= n; ++i) {
        dp[i] = 1;
    }

    topoSort(n);

    int maxVisited = 0;
    for (int i = 1; i <= n; ++i) {
        maxVisited = std::max(maxVisited, dp[i]);
    }

    std::cout << maxVisited << '\n';

    return 0;
}

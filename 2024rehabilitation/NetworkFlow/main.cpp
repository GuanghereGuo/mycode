#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <climits>
#include <queue>

#define int long long

class EdmondsKarp {
    int n, s, t;
    std::vector<std::unordered_map<int, int>> graph;  // residual graph
    std::vector<int> fa;

    int bfs() {
        std::fill(fa.begin(), fa.end(), -1);
        std::queue<std::pair<int, int>> q;
        q.push({s, INT_MAX});
        fa[s] = s;

        while (!q.empty()) {
            int now = q.front().first;
            int flow = q.front().second;
            q.pop();

            for (auto &[to, cap] : graph[now]) {
                if (fa[to] == -1 && cap > 0) {  // 没访问过，且容量大于 0
                    fa[to] = now;
                    int new_flow = std::min(flow, cap);
                    if (to == t) {
                        return new_flow;
                    }
                    q.push({to, new_flow});
                }
            }
        }
        return 0;
    }

public:
    EdmondsKarp(int n, int s, int t, std::vector<std::unordered_map<int, int>> &&graph)
        : n(n), s(s), t(t), graph(std::move(graph)), fa(n + 1) {}

    long long max_flow() {
        long long total_flow = 0;

        int new_flow;
        while ((new_flow = bfs())) {
            total_flow += new_flow;
            int cur = t;

            while (cur != s) {
                int prev = fa[cur];
                graph[prev][cur] -= new_flow;
                graph[cur][prev] += new_flow;
                cur = prev;
            }
        }
        return total_flow;
    }
};

signed main() {
    freopen("../P3376_8.in", "r", stdin);
    freopen("../out.txt", "w", stdout);

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, m, s, t;
    std::cin >> n >> m >> s >> t;
    std::vector<std::unordered_map<int, int>> graph(n + 1);

    for (int i = 0; i < m; i++) {
        int u, v, w;
        std::cin >> u >> v >> w;
        graph[u][v] += w;  // 累加边权重
    }

    EdmondsKarp ford_fulkerson(n, s, t, std::move(graph));
    std::cout << ford_fulkerson.max_flow() << std::endl;

    return 0;
}

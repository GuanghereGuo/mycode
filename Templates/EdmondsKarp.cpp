#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <climits>
#include <queue>

class EdmondsKarp {
    int n, s, t;
    std::vector<std::unordered_map<int, long long>> graph;  // residual graph
    std::vector<int> fa;

    long long bfs() {
        std::fill(fa.begin(), fa.end(), -1);
        std::queue<std::pair<int, long long>> q;
        q.emplace(s, LLONG_MAX);
        fa[s] = s;

        while (!q.empty()) {
            auto [now, flow] = q.front();
            q.pop();

            for (auto &[to, cap] : graph[now]) {
                if (fa[to] == -1 && cap > 0) {  // 没访问过，且容量大于 0
                    fa[to] = now;
                    auto new_flow = std::min(flow, cap);
                    if (to == t) {
                        int cur = t;
                        while (cur != s) {
                            int prev = fa[cur];
                            graph[prev][cur] -= new_flow;
                            graph[cur][prev] += new_flow;
                            cur = prev;
                        }
                        return new_flow;
                    }
                    q.emplace(to, new_flow);
                }
            }
        }
        return 0;
    }

public:
    EdmondsKarp(int n, int s, int t)
        : n(n), s(s), t(t), fa(n + 1), graph(n + 1) {}

    void add_edge(int u, int v, int w) {
        graph[u][v] += w;
    }

    long long max_flow() {
        long long total_flow = 0;

        long long new_flow;
        while ((new_flow = bfs())) {
            total_flow += new_flow;
        }
        return total_flow;
    }
};

signed main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, m, s, t;
    std::cin >> n >> m >> s >> t;

    EdmondsKarp edmonds_karp(n, s, t);

    for (int i = 0; i < m; i++) {
        int u, v, w;
        std::cin >> u >> v >> w;
        edmonds_karp.add_edge(u, v, w);  // 累加边权重
    }

    std::cout << edmonds_karp.max_flow() << std::endl;
}

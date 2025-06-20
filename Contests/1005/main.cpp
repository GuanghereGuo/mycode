#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <unordered_map>

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

    std::string find_flow_directions(int n, int m, const std::vector<int> &store_u) {
        std::string ret;
        for(int i = 1; i <= m; i++) {
            if(graph[n + i][store_u[i]] == 0) {
                ret.push_back('1');
            } else {
                ret.push_back('0');
            }
        }
        return ret;
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int t;
    std::cin >> t;

    while(t--) {
        int n, m;
        std::cin >> n >> m;
        EdmondsKarp dinic(n + m + 1, n + m + 1, 0);
        for(int i = 1, x; i <= n; i++) {
            std::cin >> x;
            dinic.add_edge(i, 0, x);
        }

        std::vector<int> store_u = {0};

        for(int i = 1, u, v; i <= m; i++) {
            std::cin >> u >> v;
            store_u.push_back(u);
            dinic.add_edge(n + i, u, 1);
            dinic.add_edge(n + i, v, 1);
            dinic.add_edge(n + m + 1, n + i, 1);
        }
        std::cout << m - dinic.max_flow() << '\n';

        std::cout << dinic.find_flow_directions(n, m, store_u) << '\n';
    }
}

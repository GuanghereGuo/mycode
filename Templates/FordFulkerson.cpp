#include <algorithm>
#include <cassert>
#include <climits>
#include <iostream>
#include <unordered_map>
#include <vector>

#define int long long

class EdmondsKarp {
    int n, s, t;
    std::vector<std::unordered_map<int, int>> graph;  // residual graph
    std::vector<bool> vis;

    int dfs(int now, int flow) {
        if (now == t) {
            return flow;
        }
        vis[now] = true;
        for (auto [to, val] : graph[now]) {  // 找到一条路即可
            if (vis[to] || val == 0) continue;//一定要判断无效边啊！！vis等着你
            int new_flow = dfs(to, std::min(flow, val));
            if (new_flow > 0) {
                graph[now][to] -= new_flow;
                graph[to][now] += new_flow;
                return new_flow;
            }
        }
        return 0;
    }

   public:
    EdmondsKarp(int n, int s, int t,
                  std::vector<std::unordered_map<int, int>> &&graph)
        : n(n), s(s), t(t), vis(n + 1), graph(std::move(graph)) {}

    long long max_flow() {
        long long ret = 0;
        int tmp;
        do {
            std::fill(vis.begin(), vis.end(), false);  // 每次都需要重新标记访问
            tmp = dfs(s, INT_MAX);
            ret += tmp;
        } while (tmp != 0);
        return ret;
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
        graph[u][v] += w;
    }

    EdmondsKarp ford_fulkerson(n, s, t, std::move(graph));
    std::cout << ford_fulkerson.max_flow() << std::endl;

    return 0;
}

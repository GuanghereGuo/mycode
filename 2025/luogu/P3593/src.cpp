//
// Created by guanghere on 25-2-24.
//
#include <iostream>
#include <queue>
#include <vector>

class Solution {
    struct Edge {
        int to, val;
    };

    int n = 0, m = 0, k = 0, mod = 0;
    std::vector<std::vector<Edge>> og;// original graph
    std::vector<int> dis;

    void dijkstra(const int s = 1) {
        struct Node {
            int idx, dis;
            bool operator<(const Node &rhs) const {
                return dis > rhs.dis;
            }
        };
        dis.resize(n + 1, 0x3f3f3f3f);
        std::vector<bool> vis;
        vis.resize(n + 1, false);
        dis[s] = 0;
        std::priority_queue<Node> q;
        q.push({s, 0});
        while (!q.empty()) {
            auto [u, d] = q.top();
            q.pop();
            if (vis[u]) {
                continue;
            }
            vis[u] = true;
            for (const auto &[to, val] : og[u]) {
                if (dis[to] - val > dis[u]) {
                    dis[to] = dis[u] + val;
                    q.push({to, dis[to]});
                }
            }
        }
    }



public:
    Solution() {
        std::cin >> n >> m >> k >> mod;
        og.resize(n + 1);
        for (int i = 1, u, v, w; i <= m; ++i) {
            std::cin >> u >> v >> w;
            og[u].push_back({v, w});
        }
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int t;
    std::cin >> t;
    while (t--) {
        Solution solution;
    }
}

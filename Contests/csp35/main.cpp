#include <iostream>
#include <map>
#include <queue>
#include <vector>

struct Node {
    int x, y;
};

struct Station {
    int x, y, r, t;
};

struct edge {
    int to, val;
};

//heap dijkstra
struct dij_node {
    int id, val;
    bool operator<(const dij_node &rhs) const {
        return val > rhs.val;
    }
};

auto dijkstra(const std::vector<std::vector<edge>> &graph, int start) {
    std::vector<int> dist(graph.size(), 0x3f3f3f3f);
    std::vector<bool> vis(graph.size(), false);
    std::priority_queue<dij_node> pq;
    pq.push({start, 0});
    dist[start] = 0;
    while (!pq.empty()) {
        auto [id, val] = pq.top();
        pq.pop();
        if (vis[id]) {
            continue;
        }
        vis[id] = true;
        for (const auto &e : graph[id]) {
            if (dist[e.to] > dist[id] + e.val) {
                dist[e.to] = dist[id] + e.val;
                pq.push({e.to, dist[e.to]});
            }
        }
    }
    return dist;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, m;
    std::cin >> n >> m;
    //std::vector<Node> nodes(n + 1);
    std::multimap<int, std::pair<int, int>> nodes;

    std::vector<std::vector<edge>> graph(n + m + 1);

    for (int i = 1; i <= n; ++i) {
        //std::cin >> nodes[i].x >> nodes[i].y;
        int x, y;
        std::cin >> x >> y;
        nodes.insert({x, {y, i}});
        //std::cerr << "node " << i << " at " << nodes[i].x << ' ' << nodes[i].y << '\n';
    }
    for (int i = 1; i <= m; ++i) {
        int x, y, r, t;
        std::cin >> x >> y >> r >> t;
        auto it_begin = nodes.lower_bound(x - r);
        auto it_end = nodes.upper_bound(x + r);
        for (auto it = it_begin; it != it_end; ++it) {
            auto [_x, p] = *it;
            auto [_y, idx] = p;
            //std::cerr << "station " << i << " and node " << idx << "at " << _x << ' ' << _y << '\n';
            if (std::abs(_y - y) <= r) {
                graph[idx].push_back({n + i, t});
                graph[n + i].push_back({idx, t});
                //std::cerr << "add edge between station " << i << " and node " << idx << '\n';
            }
        }
        // for (int j = 1; j <= n; ++j) {
        //     if (std::abs(x - nodes[j].x) <= r && std::abs(y - nodes[j].y) <= r) {
        //         //std::cerr << "add edge between station " << i << " and node " << j << '\n';
        //         graph[n + i].push_back({j, t});
        //         graph[j].push_back({n + i, t});
        //     }
        // }
    }
    auto ans = dijkstra(graph, 1);
    if (ans[n] == 0x3f3f3f3f) {
        std::cout << "Nan\n";
    } else {
        std::cout << ans[n] / 2 << '\n';
    }
}

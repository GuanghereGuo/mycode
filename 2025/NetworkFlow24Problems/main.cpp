#include <climits>
#include <iostream>
#include <limits>
#include <queue>
#include <vector>

class MinCostMaxFlow {
    const int INF = INT_MAX;
public:
    explicit MinCostMaxFlow(int n) : n(n), adj(n + 1), dis(n + 1), vis(n + 1), cur(n + 1), ret(0) {}

    void add_edge(int u, int v, int cap, int cost) {
        adj[u].emplace_back(Edge{v, cap, cost, static_cast<int>(adj[v].size()), true});
        adj[v].emplace_back(Edge{u, 0, -cost, static_cast<int>(adj[u].size()) - 1, false});
    }

    int min_cost_max_flow(int s, int t) {
        int max_flow = 0;
        while (spfa(s, t)) {
            std::fill(vis.begin(), vis.end(), false);
            std::fill(cur.begin(), cur.end(), 0);  // Reset current arc pointers after SPFA
            int flow;
            while ((flow = dfs(s, t, INF))) {
                max_flow += flow;
            }
        }
        return max_flow;
    }

    int get_cost() const { return ret; }

    void debug_print_flows() {
        for (int i = 1; i <= n; i++) {
            for (auto &edge : adj[i]) {
                if (edge.is_positive)
                    std::cerr << i << "->" << edge.to << ": " << adj[edge.to][edge.rev].cap << '\n';
            }
        }
    }

private:
    struct Edge {
        int to, cap, cost, rev;
        bool is_positive;
    };

    int n, ret;
    std::vector<std::vector<Edge>> adj;
    std::vector<int> dis, cur;  // cur array for current arc optimization
    std::vector<bool> vis;

    bool spfa(int s, int t) {
        std::fill(dis.begin(), dis.end(), INF);
        dis[s] = 0;
        std::queue<int> q;
        q.push(s);
        vis[s] = true;

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            vis[u] = false;

            for (const auto &e : adj[u]) {
                if (e.cap > 0 && dis[e.to] > dis[u] + e.cost) {
                    dis[e.to] = dis[u] + e.cost;
                    if (!vis[e.to]) {
                        q.push(e.to);
                        vis[e.to] = true;
                    }
                }
            }
        }
        return dis[t] != INF;
    }

    int dfs(int u, int t, int flow) {
        if (u == t) return flow;
        vis[u] = true;
        int total_flow = 0;

        // Iterate from cur[u], inspired by Dinic's ptr[u]
        for (int &i = cur[u]; i < adj[u].size(); ++i) {
            auto &e = adj[u][i];
            if (!vis[e.to] && e.cap > 0 && dis[e.to] == dis[u] + e.cost) {
                int pushed = dfs(e.to, t, std::min(flow - total_flow, e.cap));
                if (pushed > 0) {
                    e.cap -= pushed;
                    adj[e.to][e.rev].cap += pushed;
                    ret += pushed * e.cost;
                    total_flow += pushed;
                    if (total_flow == flow) break;
                }
            }
        }
        vis[u] = false;
        return total_flow;
    }
};

const int inf = std::numeric_limits<int>::max();

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, m, s, t;
    std::cin >> n >> m >> s >> t;
    MinCostMaxFlow mcmf(n);
    for (int i = 1, u, v, w, c; i <= m; i++) {
        std::cin >> u >> v >> w >> c;
        mcmf.add_edge(u, v, w, c);
    }
    auto max_flow = mcmf.min_cost_max_flow(s, t);
    auto min_cost = mcmf.get_cost();
    std::cout << max_flow << " " << min_cost << '\n';
}
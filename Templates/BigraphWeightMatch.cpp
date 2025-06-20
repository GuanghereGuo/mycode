//
// Created by 24087 on 24-11-14.
//
#include <climits>
#include <iostream>
#include <map>
#include <queue>
#include <vector>

#define int long long

class MinCostMaxFlow {
    const int INF = LLONG_MAX;

   public:
    explicit MinCostMaxFlow(int n)
        : n(n), adj(n + 1), dis(n + 1), vis(n + 1), cur(n + 1), ret(0) {}

    void add_edge(int u, int v, int w, int c) {
        adj[u].emplace_back(Edge{v, w, c, static_cast<int>(adj[v].size()), true});
        adj[v].emplace_back(
            Edge{u, 0, -c, static_cast<int>(adj[u].size()) - 1, false});
    }

    int min_cost_max_flow(int s, int t) {
        int max_flow = 0;
        while (spfa(s, t)) {
            std::fill(vis.begin(), vis.end(), false);
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
                std::cerr << i << "->" << edge.to << ": "
                          << adj[edge.to][edge.rev].cap << '\n';
            }
        }
    }

    void print_ans() {
        std::map<int, int> mp;
        int nn = (n - 2) / 2;
        // std::cerr << nn << std::endl;
        for (int i = 1; i <= nn; i++) {
            for (auto &edge : adj[i]) {
                if (edge.is_positive && edge.cap == 0) {
                    mp[edge.to - nn] = i;
                }
            }
        }
        for (int i = 1; i <= nn; i++) {
            // if (mp[i] == 0) {
            //     continue;
            // }
            std::cout << mp[i] << ' ';
        }
    }

   private:
    struct Edge {
        int to, cap, cost, rev;
        bool is_positive;
    };

    int n, ret;
    std::vector<std::vector<Edge>> adj;
    std::vector<int> dis, cur;
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

        for (auto &e : adj[u]) {
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

signed main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, m;
    std::cin >> n >> m;

    MinCostMaxFlow mcmf(n * 2 + 2);

    for (int i = 1; i <= n; i++) {
        mcmf.add_edge(2 * n + 1, i, 1, 0);
        //mcmf.add_edge(i, 2 * n + 2, 1, 0);
        mcmf.add_edge(i + n, 2 * n + 2, 1, 0);
    }

    for (int i = 1, u, v, w; i <= m; i++) {
        std::cin >> u >> v >> w;
        mcmf.add_edge(u, v + n, 1, -w);
    }

    auto flow = mcmf.min_cost_max_flow(2 * n + 1, 2 * n + 2);
    auto cost = -mcmf.get_cost();

    //std::cerr << flow << '\n';
    std::cout << cost << '\n';

    mcmf.print_ans();
}
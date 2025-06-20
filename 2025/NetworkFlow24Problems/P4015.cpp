    //
    // Created by guanghere on 25-3-22.
    //
    #include <climits>
    #include <format>
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
                for(auto &edge : adj[i]) {
                    if(edge.is_positive)
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

    constexpr int INF = std::numeric_limits<int>::max();

    int main() {
        std::ios::sync_with_stdio(false);
        std::cin.tie(nullptr);
        std::cout.tie(nullptr);

        int m, n;
        std::cin >> m >> n;
        MinCostMaxFlow min_cmf(n + m + 2);
        MinCostMaxFlow max_cmf(n + m + 2);
        const int s = n + m + 1, t = n + m + 2;

        for (int i = 1, w; i <= m; i++) {
            std::cin >> w;
            min_cmf.add_edge(s, i, w, 0);
            max_cmf.add_edge(s, i, w, 0);
        }
        for (int i = 1, c; i <= n; i++) {
            std::cin >> c;
            min_cmf.add_edge(m + i, t, c, 0);
            max_cmf.add_edge(m + i, t, c, 0);
        }
        for (int i = 1, x; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                std::cin >> x;
                min_cmf.add_edge(i, m + j, INF, x);
                max_cmf.add_edge(i, m + j, INF, -x);
            }
        }
        min_cmf.min_cost_max_flow(s, t);
        max_cmf.min_cost_max_flow(s, t);
        int min_cost = min_cmf.get_cost();
        int max_cost = -max_cmf.get_cost();
        std::cout << std::format("{}\n{}\n", min_cost, max_cost);
    }
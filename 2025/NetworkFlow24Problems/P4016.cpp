//
// Created by guanghere on 25-3-21.
//
#include <assert.h>

#include <algorithm>
#include <iostream>
#include <limits>
#include <queue>
#include <valarray>
#include <vector>

class MinCostMaxFlow {
    const int INF = std::numeric_limits<int>::max();
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

int cal(int start, int n, int aver, std::vector<int> vec) {
    auto nxt = [&](int idx) {
        return idx % n + 1;
    };
    int ans = 0;
    for (int i = 0, idx = start; i < n; i++, idx = nxt(idx)) {
        int flow = vec[idx] - aver;
        ans += std::abs(flow);
        vec[nxt(idx)] += flow;
        vec[idx] = aver;
    }
    return ans;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, sum = 0 ;
    std::cin >> n;
    std::vector<int> vec(n + 1);

    for (int i = 1; i <= n; i++) {
        std::cin >> vec[i];
        sum += vec[i];
    }
    int aver = sum / n;

    int ans = 1145141919;
    for (int i = 1; i <= n; i++) {
        ans = std::min(ans, cal(i, n, aver, vec));
    }
    std::cout << ans << '\n';

    // MinCostMaxFlow mcmf(n + 2);
    //
    // for (int i = 1; i <= n; i++) {
    //     int cap = vec[i] - aver;
    //     if (cap > 0) {
    //         mcmf.add_edge(n + 1, i, cap, 0);
    //     } else if (cap < 0) {
    //         mcmf.add_edge(i, n + 2, -cap, 0);
    //     }
    //     mcmf.add_edge(i, i % n + 1, sum, 1);
    //     mcmf.add_edge(i % n + 1, i, sum, 1);
    // }
    //
    // assert(mcmf.min_cost_max_flow(n + 1, n + 2) > 0);
    // std::cout << mcmf.get_cost() << '\n';
}
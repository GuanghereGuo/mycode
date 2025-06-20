//
// Created by 24087 on 24-11-16.
//
#include <algorithm>
#include <climits>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <unordered_map>
#include <valarray>
#include <vector>

class MinCostMaxFlow {
    const int INF = INT_MAX;

   public:
    explicit MinCostMaxFlow(int n)
        : n(n), adj(n + 1), dis(n + 1), cur(n + 1), vis(n + 1) {}

    void add_edge(int u, int v, int w, int c) {
        adj[u].emplace_back(
            Edge{v, w, c, static_cast<int>(adj[v].size()), true});
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

    [[nodiscard]] int get_cost() const { return ret; }

    void debug_print_flows() {
        for (int i = 1; i <= n; i++) {
            for (auto &edge : adj[i]) {
                if (edge.is_positive)
                    std::cerr << i << "->" << edge.to << ": "
                              << adj[edge.to][edge.rev].cap << '\n';
            }
        }
    }

   private:
    struct Edge {
        int to, cap, cost, rev;
        bool is_positive;
    };

    int n, ret = 0;
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

auto calculate_factors(const int n, const std::vector<int> &vec) {
    std::unordered_map<int, int> id;
    std::vector<std::vector<int>> factors(n + 1);
    for (int i = 1; i <= n; i++) {
        //factors[i].reserve(1e4);
        for (int j = 1; j * j <= vec[i]; j++) {
            if (vec[i] % j == 0) {
                if (!id.contains(j)) {
                    id[j] = static_cast<int>(id.size()) + 1;
                }
                factors[i].push_back(j);
                if (j * j != vec[i]) {
                    factors[i].push_back(vec[i] / j);
                    if (!id.contains(vec[i] / j)) {
                        id[vec[i] / j] = static_cast<int>(id.size()) + 1;
                    }
                }
            }
        }
    }
    return std::make_pair(std::move(factors), std::move(id));
}

std::vector<int> primes;
//linear sieve
void linear_sieve(int n) {
    std::vector<int> vis(n + 1);
    for (int i = 2; i <= n; i++) {
        if (!vis[i]) {
            primes.push_back(i);
        }
        for (int j = 0; j < primes.size() && i * primes[j] <= n; j++) {
            vis[i * primes[j]] = 1;
            if (i % primes[j] == 0) {
                break;
            }
        }
    }
}

int prime_factor_exponents_sum(int x) {
    std::pmr::unordered_map<int, int> mp;
    if(mp.contains(x)) {
        return mp[x];
    }
    int ret = 0;
    for (const int i : primes) {
        if(i * i > x) {
            break;
        }
        if (x % i == 0) {
            while (x % i == 0) {
                x /= i;
                ret++;
            }
        }
    }
    if (x > 1) {
        ret++;
    }
    return mp[x] = ret;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);

    freopen("../text.in", "r", stdin);

    int n;
    std::cin >> n;

    linear_sieve(static_cast<int>(std::sqrt(1e9)) + 1);

    std::vector<int> vec(n + 1);
    for (int i = 1; i <= n; i++) {
        std::cin >> vec[i];
    }

    auto [factors, id] = calculate_factors(n, vec);

    int m = static_cast<int>(id.size());
    MinCostMaxFlow mcmf(n + m + 2);

    for (int i = 1; i <= n; i++) {
        mcmf.add_edge(n + m + 1, i, 1, 0);
        //mcmf.add_edge(i, n + m + 2, 1, 0);
        for (int j : factors[i]) {
            mcmf.add_edge(i, n + id[j], 1,
                          prime_factor_exponents_sum(j) -
                              prime_factor_exponents_sum(vec[i]));
        }
    }
    for(int i = 1; i <= m; i++){
        mcmf.add_edge(n + i, n + m + 2, 1, 0);
    }
    std::cerr << n << ' ' << m << '\n';
    mcmf.min_cost_max_flow(n + m + 1, n + m + 2);
    // auto cost = -mcmf.get_cost();
    // std::cout << cost << '\n';
}
// 6
// 2 3 5 6 10 12
#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <cmath>
#include <numeric>
#include <algorithm>

void fast_io() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
}

using ll = long long;
const ll INF = 1e18;

// Runs Dijkstra on the sparse graph of base states
std::map<ll, ll> dijkstra(ll start_node, ll n, ll k) {
    std::map<ll, ll> dist;
    if (start_node > n) return dist;

    std::priority_queue<std::pair<ll, ll>, std::vector<std::pair<ll, ll>>, std::greater<>> pq;

    ll base = start_node % k;
    ll cost = start_node / k;

    dist[base] = cost;
    pq.push({cost, base});

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        if (d > dist[u]) {
            continue;
        }

        // Option 1: Cycle edge (T1 on a base state)
        ll v_cycle = k - u;
        ll next_dist_cycle = d + 1;
        if (!dist.count(v_cycle) || next_dist_cycle < dist[v_cycle]) {
            dist[v_cycle] = next_dist_cycle;
            pq.push({next_dist_cycle, v_cycle});
        }

        // Option 2: Jump edge (T2 on a base state)
        ll y = n - std::abs((n - u) - k);
        if (y >= 0) {
            ll v_jump = y % k;
            ll cost_jump = 1 + y / k;
            ll next_dist_jump = d + cost_jump;
            if (!dist.count(v_jump) || next_dist_jump < dist[v_jump]) {
                dist[v_jump] = next_dist_jump;
                pq.push({next_dist_jump, v_jump});
            }
        }
    }
    return dist;
}

// Combines two distance maps to find the minimum meeting cost
ll combine(const std::map<ll, ll>& dist1, const std::map<ll, ll>& dist2) {
    if (dist1.empty() || dist2.empty()) return INF;

    ll min_cost = INF;

    const auto& smaller_map = (dist1.size() < dist2.size()) ? dist1 : dist2;
    const auto& larger_map = (dist1.size() < dist2.size()) ? dist2 : dist1;

    for (const auto& [node, d1] : smaller_map) {
        if (larger_map.count(node)) {
            ll d2 = larger_map.at(node);
            min_cost = std::min(min_cost, d1 + d2);
        }
    }
    return min_cost;
}

void solve() {
    ll n, k, s, t;
    std::cin >> n >> k >> s >> t;

    if (s == t) {
        std::cout << 0 << "\n";
        return;
    }

    auto dist_s = dijkstra(s, n, k);
    auto dist_t = dijkstra(t, n, k);
    auto dist_ns = dijkstra(n - s, n, k);
    auto dist_nt = dijkstra(n - t, n, k);

    ll ans = INF;
    ans = std::min(ans, combine(dist_s, dist_t));
    ans = std::min(ans, combine(dist_ns, dist_nt));
    ans = std::min(ans, combine(dist_s, dist_nt));
    ans = std::min(ans, combine(dist_ns, dist_t));

    if (ans >= INF) {
        std::cout << -1 << "\n";
    } else {
        std::cout << ans << "\n";
    }
}

int main() {
    fast_io();
    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}

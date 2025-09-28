//
// Created by guanghere on 2025/9/28.
//
#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <queue>
#include <limits>

using namespace std;
using ll = long long;
using ld = long double;


struct Point {
    ld x, y, z;
};

ld dist_sq(const Point& p1, const Point& p2) {
    return (p1.x - p2.x) * (p1.x - p2.x) +
           (p1.y - p2.y) * (p1.y - p2.y) +
           (p1.z - p2.z) * (p1.z - p2.z);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, q;
    cin >> n >> m >> q;

    vector<Point> p(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> p[i].x >> p[i].y >> p[i].z;
    }

    vector<vector<pair<int, ld>>> adj(n + 1);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        ld d_sqrt = sqrt(dist_sq(p[u], p[v]));
        adj[u].push_back({v, d_sqrt});
        adj[v].push_back({u, d_sqrt});
    }

    vector<ld> s(n + 1, numeric_limits<ld>::max());
    s[1] = 0;
    priority_queue<pair<ld, int>, vector<pair<ld, int>>, greater<pair<ld, int>>> pq;
    pq.push({0.0L, 1});

    while (!pq.empty()) {
        auto [cost, u] = pq.top();
        pq.pop();

        if (cost > s[u]) {
            continue;
        }

        for (const auto& edge : adj[u]) {
            int v = edge.first;
            ld weight = edge.second;
            if (s[u] + weight < s[v]) {
                s[v] = s[u] + weight;
                pq.push({s[v], v});
            }
        }
    }

    cout << fixed << setprecision(10);

    for (int i = 0; i < q; ++i) {
        int c;
        ld t;
        cin >> c >> t;

        if (s[c] == numeric_limits<ld>::max()) {
            cout << "impossible\n";
            continue;
        }

        ld min_s = s[c];
        ld min_t = 2.0L * min_s;

        if (t < min_t) {
            cout << "impossible\n";
        } else {
            ld fuel = t - sqrt(t * t - 4.0L * min_s * min_s);
            cout << fuel << "\n";
        }
    }
    return 0;
}

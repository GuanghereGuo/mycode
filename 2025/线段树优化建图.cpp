#include <iostream>
#include <queue>
#include <vector>
#include <climits>

#define int long long

// 线段树优化建图
class SegmentTreeGraph {
    struct Edge {
        int to, val;
    };
    int n;
    std::vector<std::vector<Edge>> tr;
    std::vector<int> idx;
    void build(const int now, const int l, const int r) {
        if (l == r) {
            idx[l] = now;
            return;
        }
        tr[now].push_back({now << 1, 0});
        tr[now].push_back({now << 1 | 1, 0});
        tr[(now << 1) + 4 * n].push_back({now + 4 * n, 0});
        tr[(now << 1 | 1) + 4 * n].push_back({now + 4 * n, 0});
        const int mid = (l + r) >> 1;
        build(now << 1, l, mid);
        build(now << 1 | 1, mid + 1, r);
    }
    void connect_point_to_range(int now, int l, int r, int L, int R, int start,
                                int val) {
        if (r < L || l > R)
            return;
        if (L <= l && r <= R) {
            //std::cerr << "l=" << l << " r=" << r << " start=" << start << " val=" << val << std::endl;
            tr[start + 4 * n].push_back({now, val});
            return;
        }
        int mid = (l + r) >> 1;
        connect_point_to_range(now << 1, l, mid, L, R, start, val);
        connect_point_to_range(now << 1 | 1, mid + 1, r, L, R, start, val);
    }
    void connect_range_to_point(int now, int l, int r, int L, int R, int dest,
                                int val) {
        if (r < L || l > R)
            return;
        if (L <= l && r <= R) {
            tr[now + 4 * n].push_back({dest, val});
            return;
        }
        int mid = (l + r) >> 1;
        connect_range_to_point(now << 1, l, mid, L, R, dest, val);
        connect_range_to_point(now << 1 | 1, mid + 1, r, L, R, dest, val);
    }

   public:
    explicit SegmentTreeGraph(const int _n)
        : n(_n), tr(_n << 3), idx(_n + 1) {
        build(1, 1, _n);
        for (int i = 1; i <= _n; ++i) {
            tr[idx[i]].push_back({idx[i] + 4 * _n, 0});
            tr[idx[i] + 4 * _n].push_back({idx[i], 0});
        }
    }
    void connect_point_to_range(int l, int r, int start, int val) {
        connect_point_to_range(1, 1, n, l, r, idx[start], val);
    }
    void connect_range_to_point(int l, int r, int dest, int val) {
        connect_range_to_point(1, 1, n, l, r, idx[dest], val);
    }
    void connect_point_to_point(int start, int dest, int val) {
        tr[idx[start] + 4 * n].push_back({idx[dest], val});
    }

    auto dijkstra(int s) {
        struct Dij_Node {
            int u, d;
            bool operator<(const Dij_Node &rhs) const { return d > rhs.d; }
        };
        std::vector<int> dis(8 * n, LLONG_MAX);
        std::vector<bool> vis(8 * n);
        std::priority_queue<Dij_Node> q;
        q.push({idx[s] + 4 * n, 0});
        dis[idx[s] + 4 * n] = 0;

        while (!q.empty()) {
            auto [u, d] = q.top();
            q.pop();
            if (vis[u]) continue;
            vis[u] = true;
            for (const auto &[to, val] : tr[u]) {
                if (vis[to])
                    continue;
                if (dis[to] - val> d) {
                    dis[to] = d + val;
                    q.push({to, dis[to]});
                }
            }
        }
        std::vector<int> ans(n + 1);
        for (int i = 1; i <= n; i++) {
            ans[i] = dis[idx[i] + 4 * n];
        }
        return ans;
    }
};

signed main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, q, s;
    std::cin >> n >> q >> s;
    SegmentTreeGraph graph(n);
    for (int i = 1, u, v, w, l, r, opt; i <= q; i++) {
        std::cin >> opt;
        switch (opt) {
            case 1:
                std::cin >> u >> v >> w;
                graph.connect_point_to_point(u, v, w);
                break;
            case 2:
                std::cin >> u >> l >> r >> w;
                graph.connect_point_to_range(l, r, u, w);
                //graph.connect_range_to_point(l, r, u, w);
                break;
            case 3:
                std::cin >> v >> l >> r >> w;
                graph.connect_range_to_point(l, r, v, w);
                //graph.connect_point_to_range(l, r, v, w);
                break;
            default:
                std::cerr << "Man! What can I say?" << std::endl;
                break;
        }
    }
    //graph.debug_print_tr();
    auto dist = graph.dijkstra(s);
    for (int i = 1; i <= n; i++) {
        std::cout << (dist[i] == LLONG_MAX ? -1 : dist[i] ) << ' ';
    }
}

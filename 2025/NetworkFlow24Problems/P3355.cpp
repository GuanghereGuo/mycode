//
// Created by guanghere on 25-3-22.
//
#include <iostream>
#include <vector>
#include <queue>
#include <limits>

class Dinic {
    struct Edge {
        int to;
        long long capacity, flow;
        Edge(int to, long long capacity): to(to), capacity(capacity), flow(0) {}
    };

    int n, source, sink;
    std::vector<std::vector<int>> adj;    // 邻接表存储边的索引
    std::vector<Edge> edges;              // 存储边的信息
    std::vector<int> level;               // 分层图
    std::vector<int> ptr;                 // 当前弧优化的指针
    const long long INF = std::numeric_limits<long long>::max(); // 无限大表示

    bool bfs() {
        std::queue<int> q;
        level.assign(n + 1, -1);           // 初始化分层图，从1开始
        level[source] = 0;
        q.push(source);

        while(!q.empty()) {
            int u = q.front();
            q.pop();
            for(int idx : adj[u]) {
                const Edge &e = edges[idx];
                if(e.flow < e.capacity && level[e.to] == -1) {
                    level[e.to] = level[u] + 1;
                    q.push(e.to);
                }
            }
        }

        return level[sink] != -1;          // 是否能够到达汇点
    }

    long long dfs(int u, long long pushed) {
        if(u == sink) return pushed;
        for(int &i = ptr[u]; i < adj[u].size(); ++i) {
            int idx = adj[u][i];
            Edge &e = edges[idx];
            if(level[u] + 1 != level[e.to] || e.flow == e.capacity) continue;
            long long flow = dfs(e.to, std::min(pushed, e.capacity - e.flow));
            if(flow > 0) {
                e.flow += flow;
                edges[idx ^ 1].flow -= flow;  // 更新反向边
                return flow;
            }
        }
        return 0;
    }

public:
    Dinic(int n, int source, int sink): n(n), source(source), sink(sink) {
        adj.resize(n + 1);    // 从1开始，多分配一个位置
        level.resize(n + 1);
        ptr.resize(n + 1);
    }

    void add_edge(int u, int v, long long capacity) {
        edges.emplace_back(v, capacity);    // 正向边
        edges.emplace_back(u, 0);           // 反向边，容量为0
        adj[u].push_back(edges.size() - 2); // 正向边的索引
        adj[v].push_back(edges.size() - 1); // 反向边的索引
    }

    long long max_flow() {
        long long total_flow = 0;
        while(bfs()) {
            ptr.assign(n + 1, 0);           // 每次BFS后重置指针
            while(long long flow = dfs(source, INF)) {
                total_flow += flow;
            }
        }
        return total_flow;
    }

    void debug_print_flow() {
        for(int i = 1; i <= n; i++) {
            for(int idx : adj[i]) {
                if((idx & 1) == 1) {
                    continue;
                }
                const Edge &e = edges[idx];
                std::cerr << i << "->" << e.to << " " << e.flow << std::endl;
            }
        }
    }
};

int n, m;

int get_idx(int x, int y) {
    return (x - 1) * n + y;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    std::cin >> n >> m;
    int s = n * n + 1, t = n * n + 2;
    Dinic d(n * n + 2, s, t);
    std::vector blocked(n + 1, std::vector<bool>(n + 1));

    for (int i = 1, x, y; i <= m; i++) {
        std::cin >> x >> y;
        blocked[x][y] = true;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (blocked[i][j]) {
                continue;
            }
            if ((i + j) % 2 == 0) {
                d.add_edge(s, get_idx(i, j), 1);
                if (i + 2 <= n && j + 1 <= n && !blocked[i + 2][j + 1]) {
                    d.add_edge(get_idx(i, j), get_idx(i + 2, j + 1), 1);
                }
                if (i + 2 <= n && j - 1 >= 1 && !blocked[i + 2][j - 1]) {
                    d.add_edge(get_idx(i, j), get_idx(i + 2, j - 1), 1);
                }
                if (i + 1 <= n && j + 2 <= n && !blocked[i + 1][j + 2]) {
                    d.add_edge(get_idx(i, j), get_idx(i + 1, j + 2), 1);
                }
                if (i + 1 <= n && j - 2 >= 1 && !blocked[i + 1][j - 2]) {
                    d.add_edge(get_idx(i, j), get_idx(i + 1, j - 2), 1);
                }
                if (i - 1 >= 1 && j + 2 <= n && !blocked[i - 1][j + 2]) {
                    d.add_edge(get_idx(i, j), get_idx(i - 1, j + 2), 1);
                }
                if (i - 1 >= 1 && j - 2 >= 1 && !blocked[i - 1][j - 2]) {
                    d.add_edge(get_idx(i, j), get_idx(i - 1, j - 2), 1);
                }
                if (i - 2 >= 1 && j + 1 <= n && !blocked[i - 2][j + 1]) {
                    d.add_edge(get_idx(i, j), get_idx(i - 2, j + 1), 1);
                }
                if (i - 2 >= 1 && j - 1 >= 1 && !blocked[i - 2][j - 1]) {
                    d.add_edge(get_idx(i, j), get_idx(i - 2, j - 1), 1);
                }
            } else {
                d.add_edge(get_idx(i, j), t, 1);
            }

        }
    }
    auto max_flow = d.max_flow();
    std::cout << n * n - m - max_flow << std::endl;
}
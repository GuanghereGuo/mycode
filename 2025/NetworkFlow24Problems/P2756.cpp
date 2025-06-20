//
// Created by guanghere on 25-3-16.
//
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
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

    long long get_flow(int u, int v) {
        long long total_flow = 0;
        for(int idx : adj[u]) {
            if(edges[idx].to == v) {
                total_flow += edges[idx].flow;
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
    int get_v(int u) {
        for(int idx : adj[u]) {
            if(edges[idx].flow == 1) {
                return edges[idx].to;
            }
        }
        return -1;
    }
};


int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int m, n;
    std::cin >> m >> n;
    Dinic d(n + 2, n + 1, n + 2);
    while (true)
    {
        int u, v;
        std::cin >> u >> v;
        if (u == -1 && v == -1) {
            break;
        }
        d.add_edge(u, v, 1);
    }
    for (int i = 1; i <= m; i++) {
        d.add_edge(n + 1, i, 1);
    }
    for (int i = m + 1; i <= n; i++) {
        d.add_edge(i, n + 2, 1);
    }
    std::cout << d.max_flow() << std::endl;

    for (int i = 1; i <= m; i++) {
        int v = d.get_v(i);
        if (v != -1) {
            std::cout << i << " " << v << std::endl;
        }
    }

}
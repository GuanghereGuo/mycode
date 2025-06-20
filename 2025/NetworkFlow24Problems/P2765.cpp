//
// Created by guanghere on 25-3-17.
//
#include <algorithm>
#include <iostream>
#include <limits>
#include <queue>
#include <valarray>
#include <vector>

class Dinic {
public:
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
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n;
    std::cin >> n;

    constexpr int N = 1e5, source = N + 1, sink = N + 2, delta = N / 2;
    Dinic d(N + 2, source, sink);
    int max_r = 0, now = 1;
    for (int flow = 0; max_r <= n; now++) {// 最大路径覆盖 = 点数 - 最大匹配数
        d.add_edge(source, now, 1);
        d.add_edge(now + delta, sink, 1);
        for (int i = 1; i < now; i++) {
            int sum = i + now;
            int sqrt = static_cast<int>(std::sqrt(sum + 0.5));
            if (sqrt * sqrt == sum) {
                d.add_edge(i, now + delta, 1);
            }
        }
        flow += d.max_flow();
        max_r = now - flow;
    }
    int ball = now - 2;//已经超过一个，然后又被++了一次
    std::cout << ball << std::endl;

    //print_path
    std::vector<bool> vis(ball + 1);
    for (int i = 1; i <= ball; i++) {
        if (vis[i])
            continue;
        vis[i] = true;
        int now = i;
        bool flag = false;
        std::vector<int> ans(1, i);
        do {
            flag = false;
            for (int idx : d.adj[now]) {
                if (d.edges[idx].flow && d.edges[idx].to != source) {
                    int v = d.edges[idx].to - delta;
                    //std::cerr << now << " " << d.edges[idx].to << std::endl;
                    ans.push_back(v);
                    now = v;
                    flag = true;
                    vis[v] = true;
                    break;
                }
            }
        }while (flag);
        for (int i : ans) {
            std::cout << i << " ";
        }
        std::cout << '\n';
    }
}
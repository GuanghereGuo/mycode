#include <iostream>
#include <vector>
#include <queue>

// 使用 using namespace std; 在 OI/ACM 风格中很常见，以简化代码
// 但在大型项目中通常不推荐
using namespace std;

// 快速 I/O
void fast_io() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
}

// BFS 函数，用于计算从某个源点开始的可达性
// g: 图的邻接表表示
// start_node: BFS 的起始节点
// reachable: 记录每个节点是否可达的布尔向量
void bfs(int start_node, int n, const vector<vector<int>>& g, vector<bool>& reachable) {
    if (start_node > n || start_node < 1) return; // 防止起始节点无效

    queue<int> q;

    reachable.assign(n + 1, false);
    reachable[start_node] = true;
    q.push(start_node);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v : g[u]) {
            if (!reachable[v]) {
                reachable[v] = true;
                q.push(v);
            }
        }
    }
}

int main() {
    // 启用快速 I/O
    fast_io();

    int n, m;
    cin >> n >> m;

    // 邻接表来存储图和反向图
    // adj: 存储原图 G
    // rev_adj: 存储反向图 G_rev
    vector<vector<int>> adj(n + 1);
    vector<vector<int>> rev_adj(n + 1);

    // 存储所有边，以便最后遍历
    vector<pair<int, int>> edges;
    edges.reserve(m);

    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        rev_adj[v].push_back(u);
        edges.push_back({u, v});
    }

    // --- 步骤 1: 正向可达性分析 ---
    // 计算从顶点 1 出发可以到达的所有顶点
    vector<bool> reachable_from_1;
    bfs(1, n, adj, reachable_from_1);

    // --- 步骤 2: 反向可达性分析 ---
    // 计算在反向图中从顶点 n 出发可以到达的所有顶点
    // 这等价于在原图中可以到达顶点 n 的所有顶点
    vector<bool> can_reach_n;
    bfs(n, n, rev_adj, can_reach_n);

    // --- 步骤 3: 统计有效边 ---
    // 一条边 (u, v) 是有效的，当且仅当：
    // 1. 存在从 1 到 u 的路径 (reachable_from_1[u] is true)
    // 2. 存在从 v 到 n 的路径 (can_reach_n[v] is true)
    long long interesting_paths_count = 0;
    for (const auto& edge : edges) {
        int u = edge.first;
        int v = edge.second;

        // 检查两个条件是否同时满足
        if (reachable_from_1[u] && can_reach_n[v]) {
            interesting_paths_count++;
        }
    }

    // 输出结果
    cout << interesting_paths_count << endl;

    return 0;
}

//
// Created by guanghere on 25-4-6.
//
#include <functional>
#include <iostream>
#include <queue>
#include <vector>

enum Color {
    uf = 1,  // unset false
    st = 2,  // set true
    sf = 3,  // set false
    ut = 4,  // unset true
    uf2 = 5, // unset false (for tag2)
};

bool dfs(int node, const std::vector<std::vector<int>>& adj, std::vector<bool>& visited, std::vector<bool>& inPath) {
    visited[node] = true;
    inPath[node] = true;
    for (int neighbor : adj[node]) {
        if (!visited[neighbor]) {
            if (dfs(neighbor, adj, visited, inPath)) {
                return true;
            }
        } else if (inPath[neighbor]) {
            return true;
        }
    }
    inPath[node] = false;
    return false;
}

bool is_dag(const std::vector<std::vector<int>>& adj, int V) {
    std::vector<bool> visited(V + 1, false);
    std::vector<bool> inPath(V + 1, false);
    for (int i = 1; i <= V; ++i) {
        if (!visited[i]) {
            if (dfs(i, adj, visited, inPath)) {
                return false;
            }
        }
    }
    return true;
}

struct Node {
    int idx;
    Color c;
    bool operator<(const Node& other) const {
        return c > other.c;
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n;
    std::cin >> n;
    std::vector<Color> color(n + 1);
    std::vector<std::vector<int>> g(n + 1);
    std::vector<int> ufs, sfs;
    int sti = 0, uti = 0;

    for (int i = 1; i <= n; ++i) {
        std::string s1, s2;
        std::cin >> s1 >> s2;
        if (s1 == "unset") {
            if (s2 == "false") {
                color[i] = uf;
                ufs.push_back(i);
            } else if (s2 == "true") {
                color[i] = ut;
                uti = i;
            }
        } else if (s1 == "set") {
            if (s2 == "false") {
                color[i] = sf;
                sfs.push_back(i);
            } else if (s2 == "true") {
                if (sti) {
                    std::cout << -1;
                    return 0;
                }
                color[i] = st;
                sti = i;
            }
        }
    }
    g[sti].push_back(uti);

    if (!sti) {
        if (uti || !sfs.empty()) {
            std::cout << -1;
            return 0;
        }
    }

    for (int i : sfs) {
        g[sti].push_back(i);
        g[i].push_back(uti);
    }

    int m;
    std::cin >> m;
    std::pmr::vector<bool> tag1(n + 1), tag2(n + 1);
    for (int i = 1; i <= m; i++) {
        int u, v;
        std::cin >> u >> v;
        g[u].push_back(v);
        if (color[u] == uf) {
            if (color[v] == sf || color[v] == ut || color[v] == st) {
                tag1[u] = true;
            }
        }
        if (color[v] == uf) {
            if (color[u] == st || color[u] == sf || color[u] == ut) {
                tag2[v] = true;
                if (!uti || !sti) {
                    std::cout << -1;
                    return 0;
                }
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        if (tag1[i] && tag2[i]) {
            std::cout << -1;
            return 0;
        }
        if (tag2[i]) {
            color[i] = uf2;
        }
    }

    for (int i = 1; i <= n; i++) {
        std::sort(g[i].begin(), g[i].end());
        g[i].erase(std::unique(g[i].begin(), g[i].end()), g[i].end());
    }

    std::vector<int> topo;

    if (!is_dag(g, n)) {
        std::cout << -1;
        return 0;
    }

    std::vector<int> in_degree(n + 1);
    std::vector<bool> vis(n + 1);
    //std::queue<int> q;
    std::priority_queue<Node> q;
    for (int i = 1; i <= n; ++i) {
        for (int j : g[i]) {
            in_degree[j]++;
        }
    }
    for (int i = 1; i <= n; i++) {
        if (in_degree[i] == 0 && color[i] == uf) {
            q.push({i, color[i]});
        }
    }
    while (!q.empty()) {
        int now = q.top().idx;
        q.pop();
        topo.push_back(now);
        vis[now] = true;
        for (int i : g[now]) {
            in_degree[i]--;
            if (in_degree[i] == 0) {
                q.push({i, color[i]});
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        if (!vis[i] && in_degree[i] == 0) {
            q.push({i, color[i]});
        }
    }
    while (!q.empty()) {
        int now = q.top().idx;
        q.pop();
        topo.push_back(now);
        for (int i : g[now]) {
            in_degree[i]--;
            if (in_degree[i] == 0) {
                q.push({i, color[i]});
            }
        }
    }
    for (int i : topo) {
        std::cout << i << " ";
    }
}
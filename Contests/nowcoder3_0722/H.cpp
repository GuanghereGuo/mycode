//
// Created by guanghere on 25-7-22.
//
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

// 使用 C++26 [[unlikely]] 属性可以给编译器一些分支预测的提示，但对于本题逻辑影响不大。
// 这里主要采用现代 C++ 的风格和实践。

// 快速 I/O
void fast_io() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
}

const int MAXN = 1000005;
const int LOGN = 20; // 2^19 < 10^6 < 2^20

std::vector<int> adj[MAXN];
int parent[MAXN][LOGN];
int depth[MAXN];
int n;

/**
 * @brief 通过深度优先搜索构建LCA所需的父节点表和深度信息
 * @param u 当前节点
 * @param p 父节点
 * @param d 当前深度
 */
void dfs(int u, int p, int d) {
    depth[u] = d;
    parent[u][0] = p;
    for (int v : adj[u]) {
        if (v != p) {
            dfs(v, u, d + 1);
        }
    }
}

/**
 * @brief 预处理LCA，构建完整的倍增表
 */
void build_lca() {
    // 从根节点1开始DFS
    dfs(1, 0, 0);
    // 填充倍增表
    for (int j = 1; j < LOGN; ++j) {
        for (int i = 1; i <= n; ++i) {
            if (parent[i][j - 1] != 0) {
                parent[i][j] = parent[parent[i][j - 1]][j - 1];
            } else {
                parent[i][j] = 0;
            }
        }
    }
}

/**
 * @brief 获取节点u的第k个祖先
 * @param u 节点
 * @param k 祖先层级
 * @return 第k个祖先的节点编号，如果不存在则为0
 */
int get_ancestor(int u, int k) {
    if (k < 0) return 0;
    for (int j = 0; j < LOGN; ++j) {
        if ((k >> j) & 1) {
            u = parent[u][j];
            if (u == 0) [[unlikely]] break; // 到达根节点的父节点
        }
    }
    return u;
}

/**
 * @brief 计算两个节点u和v的最近公共祖先
 * @param u 节点u
 * @param v 节点v
 * @return LCA的节点编号
 */
int lca(int u, int v) {
    if (depth[u] < depth[v]) std::swap(u, v);
    u = get_ancestor(u, depth[u] - depth[v]);
    if (u == v) return u;
    for (int j = LOGN - 1; j >= 0; --j) {
        if (parent[u][j] != 0 && parent[u][j] != parent[v][j]) {
            u = parent[u][j];
            v = parent[v][j];
        }
    }
    return parent[u][0];
}

/**
 * @brief 计算两个节点u和v之间的距离
 * @param u 节点u
 * @param v 节点v
 * @return 距离
 */
int dist(int u, int v) {
    int ancestor = lca(u, v);
    return depth[u] + depth[v] - 2 * depth[ancestor];
}

/**
 * @brief 从节点u沿着到v的路径移动d步
 * @param u 起始节点
 * @param v 目标节点
 * @param d 移动步数
 * @return 到达的节点编号
 */
int move_towards(int u, int v, int d) {
    if (u == v || d == 0) return u;
    int ancestor = lca(u, v);
    int dist_u_anc = depth[u] - depth[ancestor];
    if (d <= dist_u_anc) {
        return get_ancestor(u, d);
    } else {
        int total_dist = dist(u, v);
        if (d >= total_dist) return v;
        return get_ancestor(v, total_dist - d);
    }
}

int main() {
    fast_io();

    int k;
    std::cin >> n >> k;

    for (int i = 2; i <= n; ++i) {
        int f;
        std::cin >> f;
        adj[f].push_back(i);
        adj[i].push_back(f);
    }

    build_lca();

    std::vector<int> possible_positions = {1};
    long long min_coincidence_time = -1;

    for (int i = 0; i < k; ++i) {
        int u;
        long long l, r;
        std::cin >> u >> l >> r;

        // 1. 检查当前所有可能位置是否能与目标u相遇
        for (int p : possible_positions) {
            int d = dist(p, u);
            if (d == 0) { // 初始就在目标点
                if (min_coincidence_time == -1 || l < min_coincidence_time) {
                    min_coincidence_time = l;
                }
            } else { // 需要移动
                long long arrival_time = l + d - 1;
                if (arrival_time <= r) { // 检查是否能在区间内到达
                    if (min_coincidence_time == -1 || arrival_time < min_coincidence_time) {
                        min_coincidence_time = arrival_time;
                    }
                }
            }
        }

        // 2. 更新下一阶段的可能位置集合
        std::vector<int> next_possible_positions = possible_positions;
        long long max_moves_in_interval = r - l + 1;

        for (int p : possible_positions) {
            int d = dist(p, u);
            int moves_to_make = std::min((long long)d, max_moves_in_interval);
            int new_pos = move_towards(p, u, moves_to_make);
            next_possible_positions.push_back(new_pos);
        }

        // 去重并排序，保持集合的性质
        std::sort(next_possible_positions.begin(), next_possible_positions.end());
        next_possible_positions.erase(std::unique(next_possible_positions.begin(), next_possible_positions.end()), next_possible_positions.end());

        possible_positions = std::move(next_possible_positions);
    }

    std::cout << min_coincidence_time << "\n";

    return 0;
}
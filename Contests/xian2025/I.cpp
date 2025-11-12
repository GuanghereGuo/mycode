//
// Created by guanghere on 2025/11/12.
//
#include <bits/stdc++.h>

int n;
std::vector<bool> vis;
std::vector<std::vector<int>> A, tr;


signed main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n;
    A.resize(n + 1, std::vector<int>(n + 1));
    for (int i = 1; i <= n; ++i) {
        for (int j = i; j <= n; ++j) {
            std::cin >> A[i][j];
            A[j][i] = A[i][j];
        }
    }

    tr.resize(n + 1, std::vector<int>());
    vis.resize(n + 1, false);
    std::queue<int> leaf;
    std::set<int> left;
    for (int i = 2; i <= n; i++) {
        left.insert(i);
    }
    leaf.push(1);
    while (!leaf.empty() && !left.empty()) {
        int root = leaf.front();
        leaf.pop();
        for (auto it = left.begin(); it != left.end();) {
            int i = *it;
            if (A[root][i] == (A[root][root] ^ A[i][i])) {
                tr[root].push_back(i);
                tr[i].push_back(root);
                vis[i] = true;
                leaf.push(i);
                left.erase(it++);
            } else {
                ++it;
            }
        }
    }
    for (int i = 1; i <= n; ++i) {
        for (int j : tr[i]) {
            if (i < j)
                std::cout << i << " " << j << "\n";
        }
        std::cout << "\n";
    }
}
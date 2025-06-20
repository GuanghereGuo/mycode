//
// Created by 24087 on 24-11-6.
//
#include <algorithm>
#include <functional>
#include <iostream>
#include <set>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n;
    std::cin >> n;
    std::vector<std::vector<int>> g(n + 1);
    std::vector<int> in_degree(n + 1), ans;

    for (int i = 1, x; i <= n; i++) {
        while (true) {
            std::cin >> x;
            if (x == 0) break;
            g[i].push_back(x);
        }
    }

    for(int i = 1; i <= n; i++) {
        for(int j : g[i]) {
            in_degree[j]++;
        }
    }

    std::function<void(int)> dfs = [&](int dep) {
        if(dep == n) {
            for(int & an : ans) {
                std::cout << an << ' ';
            }
            std::cout << '\n';
        }
        for(int i = 1; i <= n; i++) {
            if(in_degree[i] == 0) {
                in_degree[i] = -1;
                for(int j : g[i]) {
                    in_degree[j]--;
                }
                ans.push_back(i);
                dfs(dep + 1);
                ans.pop_back();
                for(int j : g[i]) {
                    in_degree[j]++;
                }
                in_degree[i] = 0;
            }
        }
    };

    dfs(0);

}
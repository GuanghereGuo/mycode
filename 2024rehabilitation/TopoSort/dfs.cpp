//
// Created by 24087 on 24-11-6.
//
#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

class TopoSort {
    int n, tot = 0;
    std::vector<std::vector<int>> g;
    std::vector<int> ans, topo_order;

    void dfs(int now) {
        for(auto i : g[now]) {
            if(topo_order[i]) {
                continue;
            }
            dfs(i);
        }
        topo_order[now] = ++tot;
        ans.push_back(now);
    }

   public:
    TopoSort(int _n, std::vector<std::vector<int>> _g)
        : n(_n), g(std::move(_g)), topo_order(_n + 1) {}

    auto sort() {
        for(int i = 1; i <= n; i++) {
            if(!topo_order[i]) {
                dfs(i);
            }
        }
        std::reverse(ans.begin(), ans.end());
        return ans;
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n;
    std::cin >> n;
    std::vector<std::vector<int>> g(n + 1);

    for (int i = 1, x; i <= n; i++) {
        while (true) {
            std::cin >> x;
            if (x == 0) break;
            g[i].push_back(x);
        }
    }
    auto ans = TopoSort(n, std::move(g)).sort();
    for (auto i : ans) {
        std::cout << i << ' ';
    }
}
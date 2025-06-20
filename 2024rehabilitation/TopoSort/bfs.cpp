//
// Created by 24087 on 24-11-6.
//
#include <iostream>
#include <queue>
#include <vector>

class TopoSort {
    int n;
    std::vector<std::vector<int>> g;
    std::vector<int> in_degree, ans;

    void bfs() {
        std::queue<int> q;
        for(int i = 1; i <= n; i++) {
            if(in_degree[i] == 0) {
                q.push(i);
            }
        }
        while(!q.empty()) {
            int now = q.front();
            q.pop();
            ans.push_back(now);
            for(auto nxt : g[now]) {
                if(--in_degree[nxt] == 0) {
                    q.push(nxt);
                }
            }
        }
    }

public:
    TopoSort(int _n, std::vector<std::vector<int>> _g) : n(_n), g(std::move(_g)), in_degree(_n + 1) {
        for(int i = 1; i <= _n; i++) {
            for(int j : g[i]) {
                in_degree[j]++;
            }
        }
    }

    auto sort() {
        bfs();
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

    for(int i = 1, x; i <= n; i++) {
        while(true) {
            std::cin >> x;
            if(x == 0) break;
            g[i].push_back(x);
        }
    }
    auto ans = TopoSort(n, std::move(g)).sort();
    for(auto i : ans) {
        std::cout << i << ' ';
    }
}
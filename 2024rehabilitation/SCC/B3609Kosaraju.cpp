//
// Created by 24087 on 24-11-7.
//
#include <utility>
#include <algorithm>
#include <iostream>
#include <vector>

class Kosaraju {
    int n, cnt = 0;
    std::vector<std::vector<int>> g, scc, rev;
    std::vector<int> topo, color;
    std::vector<bool> vis;

    void topo_sort(int now) {
        vis[now] = true;
        for(auto nxt : g[now]) {
            if(!vis[nxt]) {
                topo_sort(nxt);
            }
        }
        topo.push_back(now);
    }
    void dfs(int now) {
        color[now] = cnt;
        scc.back().push_back(now);
        for(auto nxt : rev[now]) {
            if(!color[nxt]) {
                dfs(nxt);
            }
        }
    }
    void calculate() {
        for(int i = 1; i <= n; i++) {
            if(!vis[i]) {
                topo_sort(i);
            }
        }
        for(auto it = topo.rbegin(); it != topo.rend(); it++) {
            if(!color[*it]) {
                scc.emplace_back();
                cnt++;
                dfs(*it);
            }
        }
    }
   public:
    Kosaraju(const int _n, std::vector<std::vector<int>> _vec)
        : n(_n), g(std::move(_vec)), scc(1), rev(_n + 1), color(_n + 1), vis(_n + 1) {
        for (auto &vec : g) {
            std::sort(vec.begin(), vec.end());
            vec.erase(std::unique(vec.begin(), vec.end()), vec.end());
        }
        for(auto i = 1; i <= _n; i++) {
            for(auto j : g[i]) {
                rev[j].push_back(i);
            }
        }
        calculate();
    }
    auto get_color() { return std::move(color); }
    auto get_topo() { return std::move(topo); }
    auto get_cnt() const { return cnt; }
    auto get_scc() {
        for(auto &vec : scc) {
            std::sort(vec.begin(), vec.end());
        }
        return std::move(scc);
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<int>> vec(n + 1);
    for (int i = 0, u, v; i < m; ++i) {
        std::cin >> u >> v;
        if (u == v) continue;
        vec[u].push_back(v);
    }

    Kosaraju kosaraju(n, std::move(vec));

    auto color = kosaraju.get_color();
    auto scc = kosaraju.get_scc();
    auto cnt = kosaraju.get_cnt();

    std::cout << cnt << '\n';

    std::vector<bool> vis(n + 1);
    for(int i = 1; i <= n; i++) {
        if(vis[i]) {
            continue;
        }
        for(auto j : scc[color[i]]) {
            std::cout << j << ' ';
            vis[j] = true;
        }
        std::cout << '\n';
    }
}
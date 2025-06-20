//
// Created by 24087 on 9/5/2024.
//

#include <iostream>
#include <numeric>
#include <vector>

class DisjointSetUnion {
public:
    int n;
    std::vector<int> fa, size;
    explicit DisjointSetUnion(const int _n, const std::string &flag) : n(_n), fa(_n + 1), size(_n + 1) {
        std::iota(fa.begin(), fa.end(), 0);
        for(int i = 1; i <= _n; i++) {
            size[i] = (flag[i - 1] == '0' ? 1 : 0);
        }
    }
    int find(const int x) {
        return fa[x] == x ? x : fa[x] = find(fa[x]);
    }
    void unite(int x, int y) {
        x = find(x);
        y = find(y);
        if(x == y) {
            return;
        }
        size[x] += size[y];
        fa[y] = x;
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int t;
    std::cin >> t;
    while (t--) {
        int n;
        std::vector<int> vec;
        std::string flag;

        std::cin >> n;
        vec.resize(n + 1);

        for(int i = 1; i <= n; i++) {
            std::cin >> vec[i];
        }
        std::cin >> flag;

        DisjointSetUnion dsu(n, flag);
        for(int i = 1; i <= n; i++) {
            dsu.unite(i, vec[i]);
        }
        for(int i = 1; i <= n; i++) {
            std::cout << dsu.size[dsu.find(i)] << ' ';
        }
        std::cout << '\n';
    }
}

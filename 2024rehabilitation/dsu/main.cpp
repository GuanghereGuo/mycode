#include <iostream>
#include <numeric>
#include <vector>

class DisjointSetUnion {
    int n;
    std::vector<int> fa, size;

public:
    explicit DisjointSetUnion(const int _n) : n(_n), fa(_n + 1), size(_n + 1, 1) {
        std::iota(fa.begin(), fa.end(), 0);
    }
    int find(const int x) {
        if (fa[x] == x)
            return x;
        return fa[x] = find(fa[x]);
    }
    void unite(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y)
            return;
        if(size[x] < size[y])
            std::swap(x, y);
        fa[y] = x;
        size[x] += size[y];
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, m;

    std::cin >> n >> m;
    DisjointSetUnion dsu(n);

    for (int i = 1; i <= m; i++) {
        char opt;
        int x, y;
        std::cin >> opt >> x >> y;
        switch (opt) {
            case '1':
                dsu.unite(x, y);
                break;
            case '2':
                std::cout << (dsu.find(x) == dsu.find(y) ? "Y\n" : "N\n");
                break;
            default:
                std::cerr << "ERR!\n";
        }
    }
}

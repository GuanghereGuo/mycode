#include <iostream>
#include <vector>

class UnionFindSet {
    int n;
    std::vector<int> fa;

   public:
    explicit UnionFindSet(const int _n) : n(_n) {
        fa.reserve(n + 1);
        for (int i = 0; i <= n; i++) {
            fa.push_back(i);
        }
    }
    void merge(int a, int b) { fa[find(a)] = find(b); }
    int find(const int x) {
        if (fa[x] == x) {
            return x;
        }
        return fa[x] = find(fa[x]);
    }
    bool check(int a, int b) { return find(a) == find(b); }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, m;
    std::cin >> n >> m;
    UnionFindSet ufs(n);

    for (int i = 1; i <= m; i++) {
        int opt, x, y;
        std::cin >> opt >> x >> y;
        switch (opt) {
            case 1:
                ufs.merge(x, y);
                break;
            case 2:
                std::cout << (ufs.check(x, y) ? "Y\n" : "N\n");
                break;
            default:
                std::cerr << "ERR!\n";
        }
    }
    return 0;
}

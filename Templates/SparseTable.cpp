//
// Created by 24087 on 24-10-21.
//
#include <cmath>
#include <iostream>
#include <vector>

class SparseTable {
    int n, log_n;
    std::vector<std::vector<int>> vec;

   public:
    SparseTable(int n, const std::vector<int> &arr)
        : n(n),
          log_n(std::floor(std::log2(n))),
          vec(n + 1, std::vector<int>(log_n + 1)) {
        for(int i = 1; i <= n; i++) {
            vec[i][0] = arr[i];
        }
        for(int j = 1; j <= log_n; j++) {
            for(int i = 1; i + (1 << j) - 1 <= n; i++) {
                vec[i][j] = std::max(vec[i][j - 1], vec[i + (1 << (j - 1))][j - 1]);
            }
        }
    }
    int query(int l, int r) {
        int k = std::floor(std::log2(r - l + 1));
        return std::max(vec[l][k], vec[r - (1 << k) + 1][k]);
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, m;
    std::cin >> n >> m;
    std::vector<int> arr(n + 1);
    for(int i = 1; i <= n; i++) {
        std::cin >> arr[i];
    }
    SparseTable st(n, arr);
    for(int i = 0; i < m; i++) {
        int l, r;
        std::cin >> l >> r;
        std::cout << st.query(l, r) << '\n';
    }
}
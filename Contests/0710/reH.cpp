//
// Created by guanghere on 25-7-12.
//
#include <bits/stdc++.h>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m, p;
    std::cin >> n >> m >> p;
    bool x;
    std::vector<std::bitset<2048>> A(n + 1);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            std::cin >> x;
            A[i][j] = x;
        }
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= p; ++j) {
            std::cin >> x;
            A[i][j + m] = x;
        }
    }

    // Gaussian elimination
    int rank = 1;
    std::vector<int> pivot_col(n + 1);

    for (int j = 1; j <= m && rank <= n; ++j) {
        int pivot_row = rank;
        while (pivot_row <= n && !A[pivot_row][j]) {
            pivot_row++;
        }

        if (pivot_row <= n) {
            std::swap(A[rank], A[pivot_row]);
            pivot_col[rank] = j;

            for (int i = 1; i <= n; ++i) {
                if (i != rank && A[i][j]) {
                    A[i] ^= A[rank];
                }
            }
            rank++;
        }
    }
    rank--;

    for (int i = rank + 1; i <= n; ++i) {
        if (A[i].any()) {
            std::cout << "No\n";
            return 0;
        }
    }

    std::cout << "Yes\n";
    std::vector<std::bitset<1001>> B(m + 1);

    // Back Substitution
    for (int i = rank; i >= 1; --i) {
        int p_col = pivot_col[i];

        // B[p_col][k] = A[i][m+k] ^ (XOR sum of A[i][j]*B[j][k] for j > p_col)

        for (int k = 1; k <= p; ++k) {
            B[p_col][k] = A[i][m + k];
        }

        for (int j = p_col + 1; j <= m; ++j) {
            if (A[i][j]) {
                B[p_col] ^= B[j];
            }
        }
    }
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= p; ++j) {
            std::cout << B[i][j] << (j == p ? "\n" : " ");
        }
    }

}
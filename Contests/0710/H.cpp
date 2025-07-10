//
// Created by guanghere on 25-7-10.
//
#include <bitset>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <iostream>

template <size_t N>
class XORSystemSolver {
private:
    size_t n;  // 未知数和方程的个数
    std::vector<std::bitset<N + 1>> matrix;  // 增广矩阵，动态分配 n 行，每行 bitset<N+1>

public:
    // 构造函数：初始化 n 个未知数和 n 个方程
    XORSystemSolver(size_t size) : n(size), matrix(size) {
        if (n > N) {
            throw std::invalid_argument("Size exceeds template parameter N");
        }
    }

    // 设置增广矩阵的系数 (row: 行, col: 列, value: 值)
    void setMatrix(size_t row, size_t col, bool value) {
        if (row >= n || col > n || col == 0) {
            throw std::out_of_range("Invalid matrix index");
        }
        matrix[row].set(col, value);
    }

    // 设置常数项 (row: 行, value: 值)
    void setConstant(size_t row, bool value) {
        if (row >= n) {
            throw std::out_of_range("Invalid matrix index");
        }
        matrix[row].set(0, value);
    }

    // 使用高斯消元法求解异或方程组
    std::vector<bool> solve() {
        for (size_t i = 1; i <= n; i++) {
            size_t cur = i - 1;  // matrix 索引从 0 开始
            while (cur < n && !matrix[cur].test(i)) cur++;
            if (cur >= n) return std::vector<bool>();  // 无解或多解
            if (cur != i - 1) std::swap(matrix[cur], matrix[i - 1]);
            for (size_t j = 0; j < n; j++) {
                if (j != i - 1 && matrix[j].test(i)) {
                    matrix[j] ^= matrix[i - 1];  // 异或消元
                }
            }
        }
        std::vector<bool> ans(n);
        for (size_t i = 0; i < n; i++) {
            ans[i] = matrix[i].test(0);  // 提取解
        }
        return ans;
    }

    // 输出增广矩阵（用于调试，可选）
    friend std::ostream& operator<<(std::ostream& os, const XORSystemSolver& solver) {
        for (size_t i = 0; i < solver.n; i++) {
            os << "[ ";
            for (size_t j = 0; j <= solver.n; j++) {
                os << solver.matrix[i].test(j) << " ";
            }
            os << "]\n";
        }
        return os;
    }
};

int main() {
    // 示例：解决以下异或方程组
    // x1 ⊕ x2 = 1
    // x2 ⊕ x3 = 0
    // x1 ⊕ x3 = 1
    XORSystemSolver<3> solver(3);

    // 设置增广矩阵
    solver.setMatrix(0, 1, true);  solver.setMatrix(0, 2, true);  solver.setConstant(0, true);
    solver.setMatrix(1, 2, true);  solver.setMatrix(1, 3, true);  solver.setConstant(1, false);
    solver.setMatrix(2, 1, true);  solver.setMatrix(2, 3, true);  solver.setConstant(2, true);

    // 调试：输出增广矩阵
    std::cout << "Augmented Matrix:\n" << solver << std::endl;

    // 求解
    std::vector<bool> solution = solver.solve();
    if (!solution.empty()) {
        std::cout << "Solution:\n";
        for (size_t i = 0; i < solution.size(); i++) {
            std::cout << "x" << (i + 1) << " = " << solution[i] << std::endl;
        }
    } else {
        std::cout << "No unique solution" << std::endl;
    }

    return 0;
}
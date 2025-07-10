//
// Created by guanghere on 25-7-10.
//
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <vector>

// 使用 C++20 特性，如果需要的话。这里我们保持简单。

constexpr double EPS = 1E-9;

class Vector {
private:
    std::vector<double> data;
    size_t sz;

public:
    // 构造函数
    explicit Vector(size_t n) : sz(n), data(n, 0.0) {}
    Vector(std::initializer_list<double> init) : data(init), sz(init.size()) {}

    // 访问元素
    double& operator[](size_t i) {
        if (i >= sz) throw std::out_of_range("Vector index out of range");
        return data[i];
    }
    const double& operator[](size_t i) const {
        if (i >= sz) throw std::out_of_range("Vector index out of range");
        return data[i];
    }

    size_t size() const { return sz; }

    // 加法
    Vector operator+(const Vector& other) const {
        if (sz != other.sz) throw std::invalid_argument("Vector sizes mismatch for addition");
        Vector res(sz);
        for (size_t i = 0; i < sz; ++i) {
            res[i] = data[i] + other[i];
        }
        return res;
    }

    // 减法
    Vector operator-(const Vector& other) const {
        if (sz != other.sz) throw std::invalid_argument("Vector sizes mismatch for subtraction");
        Vector res(sz);
        for (size_t i = 0; i < sz; ++i) {
            res[i] = data[i] - other[i];
        }
        return res;
    }

    // 标量乘法
    Vector operator*(double scalar) const {
        Vector res(sz);
        for (size_t i = 0; i < sz; ++i) {
            res[i] = data[i] * scalar;
        }
        return res;
    }

    // 点积
    double dot(const Vector& other) const {
        if (sz != other.sz) throw std::invalid_argument("Vector sizes mismatch for dot product");
        double res = 0.0;
        for (size_t i = 0; i < sz; ++i) {
            res += data[i] * other[i];
        }
        return res;
    }

    // 输出（用于调试）
    friend std::ostream& operator<<(std::ostream& os, const Vector& v) {
        os << "[ ";
        for (size_t i = 0; i < v.sz; ++i) {
            os << v[i] << " ";
        }
        os << "]";
        return os;
    }
};

class Matrix {
private:
    std::vector<std::vector<double>> data;
    size_t rows, cols;

public:
    // 构造函数
    Matrix(size_t r, size_t c) : rows(r), cols(c), data(r, std::vector<double>(c, 0.0)) {}

    // 访问行
    std::vector<double>& operator[](size_t i) {
        if (i >= rows) throw std::out_of_range("Matrix row index out of range");
        return data[i];
    }
    const std::vector<double>& operator[](size_t i) const {
        if (i >= rows) throw std::out_of_range("Matrix row index out of range");
        return data[i];
    }

    size_t getRows() const { return rows; }
    size_t getCols() const { return cols; }

    // 加法
    Matrix operator+(const Matrix& other) const {
        if (rows != other.rows || cols != other.cols) throw std::invalid_argument("Matrix dimensions mismatch for addition");
        Matrix res(rows, cols);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                res[i][j] = data[i][j] + other[i][j];
            }
        }
        return res;
    }

    // 减法
    Matrix operator-(const Matrix& other) const {
        if (rows != other.rows || cols != other.cols) throw std::invalid_argument("Matrix dimensions mismatch for subtraction");
        Matrix res(rows, cols);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                res[i][j] = data[i][j] - other[i][j];
            }
        }
        return res;
    }

    // 矩阵乘法（矩阵-矩阵）
    Matrix operator*(const Matrix& other) const {
        if (cols != other.rows) throw std::invalid_argument("Matrix dimensions mismatch for multiplication");
        Matrix res(rows, other.cols);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < other.cols; ++j) {
                for (size_t k = 0; k < cols; ++k) {
                    res[i][j] += data[i][k] * other[k][j];
                }
            }
        }
        return res;
    }

    // 矩阵-向量乘法
    Vector operator*(const Vector& v) const {
        if (cols != v.size()) throw std::invalid_argument("Matrix-Vector dimensions mismatch for multiplication");
        Vector res(rows);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                res[i] += data[i][j] * v[j];
            }
        }
        return res;
    }

    // 标量乘法
    Matrix operator*(double scalar) const {
        Matrix res(rows, cols);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                res[i][j] = data[i][j] * scalar;
            }
        }
        return res;
    }

    // 转置
    Matrix transpose() const {
        Matrix res(cols, rows);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                res[j][i] = data[i][j];
            }
        }
        return res;
    }

    // 行列式（基于参考代码，使用高斯消元，带部分选主元）
    double determinant() const {
        if (rows != cols) throw std::invalid_argument("Determinant only for square matrices");
        size_t n = rows;
        Matrix temp = *this; // 复制以避免修改原矩阵
        double det = 1.0;
        for (size_t i = 0; i < n; ++i) {
            size_t k = i;
            for (size_t j = i + 1; j < n; ++j) {
                if (std::abs(temp[j][i]) > std::abs(temp[k][i])) k = j;
            }
            if (std::abs(temp[k][i]) < EPS) {
                return 0.0;
            }
            std::swap(temp[i], temp[k]);
            if (i != k) det = -det;
            det *= temp[i][i];
            for (size_t j = i + 1; j < n; ++j) temp[i][j] /= temp[i][i];
            for (size_t j = 0; j < n; ++j) {
                if (j != i && std::abs(temp[j][i]) > EPS) {
                    for (size_t k = i + 1; k < n; ++k) {
                        temp[j][k] -= temp[i][k] * temp[j][i];
                    }
                }
            }
        }
        return det;
    }

    // 高斯消元解方程 Ax = b（返回 x，向量）
    // 假设 A 是方阵，使用带部分选主元的高斯消元
    Vector solve(const Vector& b) const {
        if (rows != cols) throw std::invalid_argument("Solve only for square matrices");
        if (rows != b.size()) throw std::invalid_argument("Matrix-Vector dimensions mismatch for solve");
        size_t n = rows;
        Matrix aug(n, n + 1); // 增广矩阵
        for (size_t i = 0; i < n; ++i) {
            for (size_t j = 0; j < n; ++j) {
                aug[i][j] = data[i][j];
            }
            aug[i][n] = b[i];
        }

        // 前向消元（带部分选主元）
        for (size_t i = 0; i < n; ++i) {
            // 找主元
            size_t k = i;
            for (size_t j = i + 1; j < n; ++j) {
                if (std::abs(aug[j][i]) > std::abs(aug[k][i])) k = j;
            }
            if (std::abs(aug[k][i]) < EPS) {
                throw std::runtime_error("Matrix is singular or nearly singular");
            }
            std::swap(aug[i], aug[k]);

            // 消元
            for (size_t j = i + 1; j < n; ++j) {
                double factor = aug[j][i] / aug[i][i];
                for (size_t p = i; p <= n; ++p) { // 从 i 开始，因为下面会置零
                    aug[j][p] -= factor * aug[i][p];
                }
            }
        }

        // 后向代换
        Vector x(n);
        for (int i = n - 1; i >= 0; --i) {
            double sum = 0.0;
            for (size_t j = i + 1; j < n; ++j) {
                sum += aug[i][j] * x[j];
            }
            x[i] = (aug[i][n] - sum) / aug[i][i];
        }
        return x;
    }

    // 输出（用于调试）
    friend std::ostream& operator<<(std::ostream& os, const Matrix& m) {
        for (size_t i = 0; i < m.rows; ++i) {
            os << "[ ";
            for (size_t j = 0; j < m.cols; ++j) {
                os << m[i][j] << " ";
            }
            os << "]\n";
        }
        return os;
    }
};

// 示例使用（可选，用于测试）
int main() {
    int n;
    std::cin >> n;

    Vector b(n);
    Matrix A(n, n);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cin >> A[i][j];
        }
        std::cin >> b[i];
    }
    try {
        Vector x = A.solve(b);
        std::cout << std::fixed << std::setprecision(2);
        for (size_t i = 0; i < x.size(); ++i) {
            std::cout << x[i] << "\n";
        }
        std::cout << "\n";
    } catch (const std::exception& e) {
        std::cout << "No Solution\n";
    }
}
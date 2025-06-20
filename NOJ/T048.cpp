//
// Created by 24087 on 24-10-9.
//
#include <iostream>
#include <vector>

void swapRows(std::vector<std::vector<double>>& matrix, int row1, int row2,
              int n) {
    for (int i = 0; i < n; i++) {
        std::swap(matrix[row1][i], matrix[row2][i]);
    }
}

double calculateDeterminant(std::vector<std::vector<double>>& matrix, int n) {
    double determinant = 1.0;

    for (int i = 0; i < n; i++) {
        if (matrix[i][i] == 0.0) {
            for (int j = i + 1; j < n; j++) {
                if (matrix[j][i] != 0.0) {
                    swapRows(matrix, i, j, n);
                    determinant *= -1.0;
                    break;
                }
            }
        }

        if (matrix[i][i] == 0.0) {
            return 0.0;
        }

        double pivot = matrix[i][i];
        determinant *= pivot;
        for (int j = i; j < n; j++) {
            matrix[i][j] /= pivot;
        }

        for (int j = i + 1; j < n; j++) {
            double factor = matrix[j][i];
            for (int k = i; k < n; k++) {
                matrix[j][k] -= factor * matrix[i][k];
            }
        }
    }

    return determinant;
}

int main() {
    int n;
    std::cin >> n;

    std::vector matrix(n, std::vector<double>(n));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cin >> matrix[i][j];
        }
    }

    double determinant = calculateDeterminant(matrix, n);
    std::cout << determinant << std::endl;
}
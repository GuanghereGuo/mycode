//
// Created by 24087 on 24-10-7.
//
#include <iostream>

int main() {
    int rows, cols, n, num_filled = 0;
    std::cin >> rows >> cols;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            std::cin >> n;
            if (n) ++num_filled;
        }
    }

    double fill_ratio = static_cast<double>(num_filled) / (rows * cols);

    if (num_filled == rows || num_filled == cols || (fill_ratio - 0.05) <= 1e-9)
        std::cout << "Yes\n";
    else
        std::cout << "No\n";
}

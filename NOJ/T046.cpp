//
// Created by 24087 on 24-10-9.
//
#include <iostream>
#include <vector>
#include <iomanip>

double average(const std::vector<double>& arr) {
    double sum = 0;
    for (double val : arr) {
        sum += val;
    }
    return sum / arr.size();
}

int main() {
    int n;
    std::cin >> n;
    std::vector<double> x(n), y(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> x[i] >> y[i];
    }

    const double x_bar = average(x), y_bar = average(y);
    double sum_up = 0, sum_down = 0;
    for (int i = 0; i < n; ++i) {
        sum_up += (x[i] - x_bar) * (y[i] - y_bar);
    }
    for (int i = 0; i < n; ++i) {
        sum_down += (x[i] - x_bar) * (x[i] - x_bar);
    }

    const double b = sum_up / sum_down;
    const double a = y_bar - b * x_bar;

    std::cout << "Y=" << std::fixed << std::setprecision(4) << a << "+" << b << "*X" << std::endl;
    return 0;
}
//真牛魔是最小二乘法啊
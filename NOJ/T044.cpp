//
// Created by 24087 on 24-10-9.
//
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <iostream>

double func1(double x) {
    return pow(x, 4) * exp(-x);
}

double func2(double x) {
    return x * x + 1;
}

double func3(double x) {
    return cos(x);
}

double func4(double x) {
    return sqrt(x) * (x - 2);
}

double func5(double x) {
    return 2 * sin(x) - 5 * cos(x);
}

double func(int m, double x) {
    switch (m) {
        case 1: return func1(x);
        case 2: return func2(x);
        case 3: return func3(x);
        case 4: return func4(x);
        case 5: return func5(x);
        default: return 0;
    }
}

double mtk(int m, double a, double b, int n) {
    srand(RAND_MAX);
    double w = b - a, sum = 0;
    for (int i = 1; i < n; ++i) {
        double x = (static_cast<double>(rand()) / RAND_MAX) * w + a;
        sum += func(m, x);
    }
    sum *= w / n;
    return sum;
}

int main() {
    int m, n;
    double a, b;
    std::cin >> m >> a >> b >> n;
    std::cout << std::fixed << std::setprecision(6) << mtk(m, a, b, n) << std::endl;
    return 0;
}

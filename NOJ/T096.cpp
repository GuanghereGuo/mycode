//
// Created by 24087 on 24-10-8.
//
#include <complex>
#include <iomanip>
#include <iostream>

int main() {
    double a, b;
    std::cin >> a >> b;
    std::cout << std::fixed << std::setprecision(4) << std::sqrt(b /a);
}
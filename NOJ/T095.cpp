//
// Created by 24087 on 24-10-8.
//
#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>

int main() {
    int n;
    std::cin >> n;
    std::ofstream fp1("rr.dat");
    for (int i = 1; i <= n; ++i) {
        fp1 << std::fixed << std::setprecision(6) << std::sqrt(i) << " ";
        std::cout << std::fixed << std::setprecision(6) << std::sqrt(i) << " ";
    }
    fp1.close();
}
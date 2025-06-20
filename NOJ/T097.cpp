//
// Created by 24087 on 24-10-8.
//
#include <iostream>
#include <iomanip>

double pi(int n) {
    double sum = 3.0;
    for (int i = 2; i <= n; ++i) {
        const double sgn = i % 2 ? -1.0 : 1.0;
        const double tmp = 4.0 / (2 * i * (2 * i - 1) * (2 * i - 2));
        if(tmp < 1e-9)
            break;
        sum += sgn * tmp;
    }
    return sum;
}

int main() {
    int n;
    std::cin >> n;
    // for(int i = 1; i <= n; ++i) {
    //     std::cout << std::fixed << std::setprecision(7) << pi(i) << std::endl;
    // }
    std::cout << std::fixed << std::setprecision(7) << pi(n);
}
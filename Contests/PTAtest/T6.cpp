//
// Created by guanghere on 25-4-12.
//
#include <assert.h>

#include <cmath>
#include <iostream>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n;
    std::cin >> n;
    const long long a = 1, b = -2 * n * n, c = -n * n * (2 * n + 1);
    //const long long delta = b * b - 4 * a * c;
    const long long sqrt_delta = 2 * n * (n + 1);
    //assert(sqrt_delta * sqrt_delta == delta);
    //long long ans = (-b + static_cast<long long>(std::sqrt(delta))) / (2 * a);
    long long ans = (-b + sqrt_delta) / (2 * a);
    for (long long i = ans; i <= ans + n; i++) {
        std::cout << i << "^2";
        if (i != ans + n) {
            std::cout << " + ";
        } else {
            std::cout << " =\n";;
        }
    }
    for (long long i = ans + n + 1; i <= ans + 2 * n; i++) {
        std::cout << i << "^2";
        if (i != ans + 2 * n) {
            std::cout << " + ";;
        } else {
            std::cout << std::endl;
        }
    }
}
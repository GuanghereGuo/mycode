//
// Created by guanghere on 25-7-29.
//
#include <iostream>

int main() {
    int n;
    std::cin >> n;
    if (n % 2 == 0) {
        std::cout << 3 * n + 2 << '\n';
    } else {
        std::cout << 3 * n + 1 << '\n';
    }
}
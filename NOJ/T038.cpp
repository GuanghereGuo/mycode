//
// Created by 24087 on 24-10-7.
//
#include <iostream>

int main() {
    int n;
    std::cin >> n;

    while (n != 1) {
        std::cout << n << ' ';
        if (n & 1)
            n = 3 * n + 1;
        else n /= 2;
    }
    std::cout << 1;
}
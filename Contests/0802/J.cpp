//
// Created by guanghere on 25-8-2.
//
#include <iostream>
#include <algorithm>

int main() {
    int a, b;
    std::cin >> a >> b;
    if (a & 1) {
        std::swap(a, b);
    }
    std::cout << (a > b ? 2 : 1);
}
//
// Created by 24087 on 24-10-8.
//
#include <iostream>

using ull = unsigned long long;

ull achermann(ull m, ull n) {
    if (m == 0) return n + 1;
    if (n == 0) return achermann(m - 1, 1);
    return achermann(m - 1, achermann(m, n - 1));
}

int main() {
    int n, m;
    std::cin >> m >> n;
    std::cout << achermann(m, n) << std::endl;
}
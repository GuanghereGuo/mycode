//
// Created by guanghere on 25-4-12.
//
#include <format>
#include <iostream>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n;
    std::cin >> n;

    std::cout << std::format("{} {} {}\n", n / 15, n / 20, n * 90);
}
//
// Created by guanghere on 25-4-12.
//
#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

int frac(int n) {
    int f = 1;
    for (int i = 1; i <= n; i++) {
        f *= i;
    }
    return f;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n;
    std::cin >> n;
    std::vector<int> v(n), vec(n), nums;
    int num = 0;
    for (int i = 0; i < n; i++) {
        std::cin >> vec[i];
    }
    for (int i = 0; i < frac(n) / 2; i++) {
        for (int j = 0; j < n; j++) {
            std::cout << vec[(j + i) % n];
        }
        std::cout << '\n';
    }
}
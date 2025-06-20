//
// Created by 24087 on 24-9-28.
//
#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<int> vec(n);

    for (int i = 0; i < n; i++) {
        std::cin >> vec[i];
    }

    std::sort(vec.begin(), vec.end(), std::greater<>());

    int i;
    for (i = 0; i < n - 2 && vec[i] >= vec[i + 1] + vec[i + 2]; i++) {
    }

    if (i == n - 2) {
        std::cout << -1;
    } else {
        std::cout << vec[i] << ' ' << vec[i + 1] << ' ' << vec[i + 2];
    }
}
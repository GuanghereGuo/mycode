//
// Created by 24087 on 9/6/2024.
//
#include <iostream>
#include <vector>
#include <algorithm>
#include <ranges>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, m;
    std::cin >> n >> m;
    std::vector<int> vec(n + 1);
    for(int i = 1; i <= n; i++) {
        std::cin >> vec[i];
    }
    for(int i = 1; i <= m; i++) {
        int x;
        std::cin >> x;
        auto result = std::ranges::lower_bound(vec.begin() + 1, vec.end(), x);
        if(result == vec.end() || *result != x) {
            std::cout << -1 << ' ';
        } else {
            std::cout << result - vec.begin() << ' ';
        }
    }
}

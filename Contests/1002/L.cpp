//
// Created by 24087 on 24-10-2.
//
#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

int main() {

    using ull = unsigned long long;

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int t;
    std::cin >> t;

    while(t--) {
        int n, k;
        std::cin >> n >> k;
        std::vector<ull> vec(n);
        for(int i = 0; i < n; i++) {
            std::cin >> vec[i];
        }
        std::sort(vec.begin(), vec.end(), std::greater<>());
        std::cout << std::max(vec[0], std::accumulate(vec.begin() + k, vec.end(), 0ull)) << '\n';
    }
}
//
// Created by guanghere on 2025/10/3.
//
#include <bits/stdc++.h>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t;
    std::cin >> t;
    while (t--) {
        int n;
        std::cin >> n;
        std::vector<int> vec(n);
        for (int i = 0; i < n; ++i) {
            std::cin >> vec[i];
        }
        std::ranges::sort(vec);
        vec.erase(std::unique(vec.begin(), vec.end()), vec.end());
        std::cout << 2 * vec.size() - 1 << "\n";
    }
}
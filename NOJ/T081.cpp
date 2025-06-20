//
// Created by 24087 on 24-9-26.
//
#include <iostream>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, maxn = -1;
    std::cin >> n;
    std::vector<int> vec(n + 1);

    for(int i = 1; i <= n; i++) {
        std::cin >> vec[i];
        vec[i] = std::max(vec[i], vec[i] + vec[i - 1]);
        maxn = std::max(maxn, vec[i]);
    }
    std::cout << maxn;
}
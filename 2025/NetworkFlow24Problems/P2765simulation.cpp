//
// Created by guanghere on 25-3-17.
//
#include <algorithm>
#include <iostream>
#include <limits>
#include <queue>
#include <valarray>
#include <vector>

bool is_square(int n) {
    int sqrt = static_cast<int>(std::sqrt(n));
    return sqrt * sqrt == n;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int K;
    std::cin >> K;
    std::vector<std::vector<int>> ans;

    int n = 1;
    for (; ans.size() <= K; n++) {
        bool flag = false;
        for (auto &vec : ans) {
            if (is_square(vec.back() + n)) {
                vec.push_back(n);
                flag = true;
                break;
            }
        }
        if (!flag) {
            ans.push_back({n});
        }
    }
    ans.pop_back();
    std::cout << n - 2 << std::endl;
    for (const auto &vec : ans) {
        for (int i : vec) {
            std::cout << i << " ";
        }
        std::cout << std::endl;
    }
}
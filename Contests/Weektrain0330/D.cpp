//
// Created by guanghere on 25-3-30.
//
#include <algorithm>
#include <iostream>
#include <vector>
#define int long long

signed main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n;
    std::cin >> n;
    std::vector<int> stk, vec(n + 1), ans(n + 1), ans1(n + 1);
    int x = 0, h = 0;
    for (int i = 1; i <= n; ++i) {
        std::cin >> vec[i];
        h = std::max(vec[i], h);
    }
    for (int i = n; i > 0; i--) {
        while (!stk.empty() && vec[stk.back()] <= vec[i]) {
            stk.pop_back();
        }
        ans[i] = stk.empty() ? 1e6 : stk.back();
        stk.push_back(i);
    }
    stk.clear();
    for (int i = 1; i <= n; i++) {
        while (!stk.empty() && vec[stk.back()] <= vec[i]) {
            stk.pop_back();
        }
        ans1[i] = stk.empty() ? 1e6 : stk.back();
        stk.push_back(i);
    }
    for (int i = 1; i <= n; ++i) {
        if (vec[i] != h) {
            x +=
                std::min(std::abs(ans[i] - i), std::abs(ans1[i] - i));
        }
    }
    std::cout << x << std::endl;
    // for (int i = 1; i <= n; ++i) {
    //     std::cerr << ans[i] << " ";
    // }
    // std::cerr << std::endl;
    // for (int i = 1; i <= n; ++i) {
    //     std::cerr << ans1[i] << " ";
    // }
}
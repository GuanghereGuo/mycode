//
// Created by guanghere on 2025/11/12.
//
#include <bits/stdc++.h>

int calculate(std::vector<int>& vec, int n) {
    int s = 0;
    for (int i = 1; i <= n; ++i) {
        if (s >= vec[i]) {
            s++;
        } else {
            s--;
        }
    }
    return s;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n;
    std::cin >> n;
    std::vector<int> vec(n + 1);
    for (int i = 1; i <= n; ++i) {
        std::cin >> vec[i];
    }
    sort(vec.begin() + 1, vec.end());
    int result1 = calculate(vec, n);
    std::reverse(vec.begin() + 1, vec.end());
    int result2 = calculate(vec, n);
    std::cout << result1 << " " << result2 << "\n";
    return 0;
}
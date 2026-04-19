//
// Created by guanghere on 2026/4/19.
//
#include <bits/stdc++.h>

int main() {

    int t;
    std::cin >> t;
    while (t--) {
        int n;
        std::cin >> n;
        int x;
        std::cin >> x;
        bool flag = true;
        for (int i = 1, y; i < n; i++) {
            std::cin >> y;
            if (y != x) {
                flag = false;
            }
        }
        std::cout << (flag ? n : n - 1) << '\n';
    }


}
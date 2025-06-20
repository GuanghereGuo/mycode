//
// Created by 24087 on 9/5/2024.
//
#include <cmath>
#include <iostream>



int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int t;
    std::cin >> t;
    while(t--) {
        int l, r;
        std::cin >> l >> r;
        int L = 1 , R = std::sqrt(r - l) * 2 + 100;
        while(L + 1 < R) {
            int mid = (L + R) / 2;
            if(0.5 * mid * (mid - 1) + l <= r) {
                L = mid;
            } else {
                R = mid;
            }
        }
        std::cout << L << '\n';
    }
}

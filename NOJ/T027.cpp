//
// Created by 24087 on 24-10-5.
//
#include <iostream>

int main() {
    int n, k, ans = 0;
    std::cin >> n >> k;
    for(int i = 1; i <= n; i++) {
        ans += k % i;
    }
    std::cout << ans;
}
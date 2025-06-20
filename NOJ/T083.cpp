//
// Created by 24087 on 24-9-28.
//
#include <iostream>
#include <array>

int main() {
    std::array<int, 31> dp = {0};
    dp[3] = 1;

    for(int i = 4; i <= 30; i++) {
        dp[i] = 2 * dp[i - 1] + (1 << (i - 4)) - dp[i - 4];
    }
    int n;
    while(std::cin >> n && n > 0) {
        std::cout << dp[n] << '\n';
    }
}
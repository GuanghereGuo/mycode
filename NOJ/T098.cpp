//
// Created by 24087 on 24-10-8.
//
#include <array>
#include <iostream>

int main() {
    int n;
    std::cin >> n;
    std::array<int, 4> coin = {10, 5, 2, 1}, ans = {0, 0, 0, 0};
    for(int i = 0; i < 4; i++) {
        while(n - coin[i] >= 0) {
            n -= coin[i];
            ++ans[i];
        }
    }

    for(int i = 3; i >= 0; i--) {
        if(ans[i] == 0)
            continue;
        std::cout << coin[i] << '=';
        std::cout << ans[i] << '\n';
    }

}
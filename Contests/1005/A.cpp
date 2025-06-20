//
// Created by 24087 on 24-10-5.
//
#include <iostream>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int t;
    std::cin >> t;

    while(t--) {
        int k;
        std::cin >> k;
        int cnt = 0;
        if(k > 12) {
            std::cout << 0 << '\n';
            continue;
        }
        for(int i = 1; i <= 6; i++) {
            for(int j = i; j <= 6; j++) {
                if(i + j == k) {
                    cnt++;
                }
            }
        }
        std::cout << cnt << '\n';
    }
}
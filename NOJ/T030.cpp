//
// Created by 24087 on 24-10-6.
//
#include <iostream>

#define int long long

signed main() {
    int n;
    std::cin >> n;
    for(int i = 0; i < n; i++) {
        for(int j = i + 1; j < n - i - j; j++) {
            int c = n - i - j;
            if(c * c == i * i + j * j) {
                std::cout << i * j * c % (1ll << 32);
                return 0;
            }
        }
    }
}
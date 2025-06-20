//
// Created by 24087 on 24-9-26.
//
#include <iostream>

int main() {
    int n;
    std::cin >> n;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            std::cout << std::abs(j - i) << ' ';
        }
        std::cout << std::endl;
    }
}
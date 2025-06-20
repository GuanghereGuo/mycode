//
// Created by 24087 on 9/3/2024.
//
#include <iostream>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int t;
    std::cin >> t;
    while (t--) {
        int ones, twos;
        std::cin >> ones >> twos;
        if (ones % 2 != 0) {
            std::cout << "no\n";
        } else if (twos % 2 == 0) {
            std::cout << "yes\n";
        } else if (ones >= 2) {
            std::cout << "yes\n";
        } else {
            std::cout << "no\n";
        }
    }
}

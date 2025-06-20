//
// Created by 24087 on 24-9-25.
//
#include <iostream>

int main() {
    unsigned long long a, b, m;
    std::cin >> a >> b >> m;
    std::cout << static_cast<unsigned long long>(
        static_cast<__int128>(a) % static_cast<__int128>(m) *
        static_cast<__int128>(b) % static_cast<__int128>(m));
}

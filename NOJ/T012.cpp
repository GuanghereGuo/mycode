//
// Created by 24087 on 24-9-25.
//
#include <cmath>
#include <iostream>

int main() {
    int t;
    std::cin >> t;
    while(t--) {
        using ull = unsigned long long;
        int n;
        std::cin >> n;
        const ull div_by_3 = (n - 1) / 3;
        const ull div_by_5 = (n - 1) / 5;
        const ull div_by_15 = (n - 1) / 15;
        const ull sum_of_3 = div_by_3 * 3 + div_by_3 * (div_by_3 - 1) * 3 / 2;
        const ull sum_of_5 = div_by_5 * 5 + div_by_5 * (div_by_5 - 1) * 5 / 2;
        const ull sum_of_15 = div_by_15 * 15 + div_by_15 * (div_by_15 - 1) * 15 / 2;
        std::cout << (sum_of_3 + sum_of_5 - sum_of_15) % static_cast<ull>(std::pow(2, 32)) << '\n';
    }
}



//
// Created by 24087 on 24-10-10.
//
#include <array>
#include <iostream>

int main() {
    constexpr std::array<int, 4> l3s2 = {0, 5, 3, 1};
    int small_packages, medium_packages, large_packages, extra_large_packages,
        double_extra_large_packages, triple_extra_large_packages;
    while (true) {
        std::cin >> small_packages >> medium_packages >> large_packages >>
            extra_large_packages >> double_extra_large_packages >>
            triple_extra_large_packages;
        if ((small_packages + medium_packages + large_packages +
             extra_large_packages + double_extra_large_packages +
             triple_extra_large_packages) == 0)
            break;
        int total_packages = (large_packages + 3) / 4 + extra_large_packages +
                             double_extra_large_packages +
                             triple_extra_large_packages;
        int remaining_medium_packages =
            5 * extra_large_packages + l3s2[large_packages % 4];
        if (medium_packages > remaining_medium_packages)
            total_packages +=
                (medium_packages - remaining_medium_packages + 8) / 9;
        int remaining_small_packages =
            36 * total_packages - 36 * triple_extra_large_packages -
            25 * double_extra_large_packages - 16 * extra_large_packages -
            9 * large_packages - 4 * medium_packages;
        if (small_packages > remaining_small_packages)
            total_packages +=
                (small_packages - remaining_small_packages + 35) / 36;
        std::cout << total_packages << std::endl;
    }
}
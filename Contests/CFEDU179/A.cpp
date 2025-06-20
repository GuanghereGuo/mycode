//
// Created by guanghere on 25-6-3.
//

#include <iostream>
#include <array>

std::array<int, 3> get_order(std::array<int, 3> a) {
    std::array<int, 3> order = {0, 1, 2};
    if (a[0] > a[1]) {
        std::swap(order[0], order[1]);
        std::swap(a[0], a[1]);
    }
    if (a[1] > a[2]) {
        std::swap(order[1], order[2]);
        std::swap(a[1], a[2]);
    }
    if (a[0] > a[1]) {
        std::swap(order[0], order[1]);
        std::swap(a[0], a[1]);
    }
    return order;
}

int main() {
    int t;
    std::cin >> t;

    while (t--) {
        int target;
        std::cin >> target;
        std::array<int, 3> a = {1, 1, 0};
        int ans = 2;
        while (a[0] < target || a[1] < target || a[2] < target) {
            auto order = get_order(a);
            a[order[0]] = std::min(target, 2 * a[order[1]] + 1);
            ans++;
        }
        std::cout << ans << '\n';
    }
}
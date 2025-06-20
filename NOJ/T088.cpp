//
// Created by 24087 on 24-9-28.
//
#include <algorithm>
#include <iostream>
#include <vector>

struct Order {
    int end_time, idx;
    Order(const int _e, const int _i) : end_time(_e), idx(_i) {}
};

int main() {
    int n;
    std::cin >> n;

    std::vector<Order> vec;
    for (int i = 1; i <= n; i++) {
        int t, d;
        std::cin >> t >> d;
        vec.emplace_back(t + d, i);
    }

    std::sort(vec.begin(), vec.end(), [](const Order a, const Order b) -> bool {
        return a.end_time < b.end_time;
    });

    for(auto [_, idx] : vec) {
        std::cout << idx << ' ';
    }
}
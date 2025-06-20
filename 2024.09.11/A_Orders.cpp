//
// Created by 24087 on 9/11/2024.
//
#include <algorithm>
#include <iostream>
#include <queue>

#define int long long

signed main() {
    std::ios::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;
    while (t--) {
        int n, k;
        std::cin >> n >> k;
        std::vector<std::pair<int, int>> orders;
        for (int i = 0; i < n; i++) {
            int a, b;
            std::cin >> a >> b;
            orders.emplace_back(a, b);
        }
        std::ranges::sort(orders);
        int now = 0, num_of_product = 0;
        bool flag = true;
        for (const auto &[fst, snd] : orders) {
            num_of_product += (fst - now) * k;
            now = fst;
            num_of_product -= snd;
            std::cerr << num_of_product <<'\n';
            if (num_of_product < 0) {
                flag = false;
                break;
            }
        }
        if (flag) {
            std::cout << "Yes\n";
        } else {
            std::cout << "No\n";
        }
    }
}

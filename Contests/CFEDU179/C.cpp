//
// Created by guanghere on 25-6-3.
//
#include <iostream>
#include <vector>
#include <limits>

#define int long long

signed main() {
    int t;
    std::cin >> t;

    while (t--) {
        int n;
        std::cin >> n;
        std::vector<int> vec(n + 1);
        for (int i = 1; i <= n; ++i) {
            std::cin >> vec[i];
        }

        int max_len = 0, co_val = 0, min_cost = std::numeric_limits<int>::max(), now_len = 1, val = vec[1];

        for (int i = 2; i <= n; ++i) {
            if (vec[i] == val) {
                now_len++;
            } else {
                if ((n - now_len) * val < min_cost) {
                    max_len = now_len;
                    co_val = val;
                    min_cost = (n - now_len) * val;
                }
                now_len = 1;
                val = vec[i];
            }
        }
        if ((n - now_len) * val < min_cost) {
            max_len = now_len;
            co_val = val;
            min_cost = (n - now_len) * val;
        }
        std::cout << min_cost << '\n';
    }
}

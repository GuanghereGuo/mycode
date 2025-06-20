//
// Created by guanghere on 25-2-23.
//
#include <algorithm>
#include <cmath>
#include <functional>
#include <iostream>
#include <vector>

signed main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    std::vector<int> last_from(2e6 + 1, 1),
        change_number(2e6 + 1, 1), contribution(2e6 + 1);
    std::vector<std::vector<int>> factors(2e6 + 1);

    for (int i = 2; i <= 2e6; i++) {
        for (int j = 2; i * j <= 2e6; j++) {
            factors[i * j].push_back(i);
            if (change_number[i] + 1 > change_number[i * j]) {
                change_number[i * j] = change_number[i] + 1;
                last_from[i * j] = i;
            }
        }
    }

    std::vector<long long> ans(2e6 + 1);
    ans[1] = 1;
    for (int i = 2; i <= 2e6; i++) {
        std::function<long long(int)> get_last = [&](int x) -> long long {
            if (x < i) {
                contribution[x]++;
            }
            if (x == 1) {
                return 1;
            }
            // contribution[last_from[i]]++;
            return get_last(last_from[x]) + i / last_from[x] - x / last_from[x] + 1;
        };
        ans[i] = ans[i - 1] + i - 2;
        for (auto j : factors[i]) {
            ans[i] += contribution[j];
        }
        ans[i] += get_last(i);
    }

    int t;
    std::cin >> t;

    for (int i = 1; i <= t; i++) {
        int n;
        std::cin >> n;
        std::cout << ans[n] << '\n';
    }
}


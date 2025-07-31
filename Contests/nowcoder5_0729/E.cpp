//
// Created by guanghere on 25-7-29.
//
#include <iostream>
#include <vector>
#include <numeric>

#define int long long

signed main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    int total_sum = 0;
    constexpr int max_bits = 28;

    for (int k = 0; k < max_bits; ++k) {
        long long c0e = 0, c0o = 0, c1e = 0, c1o = 0;

        long long mask = (1LL << k) - 1;

        for (int val : a) {
            int lower_bits = val & mask;
            int popcnt = std::popcount(static_cast<unsigned int>(lower_bits));

            if ((val >> k) & 1) {
                if (popcnt % 2 == 0) {
                    c1e++;
                } else {
                    c1o++;
                }
            } else {
                if (popcnt % 2 == 0) {
                    c0e++;
                } else {
                    c0o++;
                }
            }
        }

        long long count_k = (c0e * c1e) + (c0o * c1o);
        total_sum += count_k * (1LL << k);
    }

    std::cout << total_sum << std::endl;

    return 0;
}

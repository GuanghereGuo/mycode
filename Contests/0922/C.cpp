//
// Created by 24087 on 24-9-25.
//
#include <algorithm>
#include <iostream>
#include <vector>
#include <climits>

#define int unsigned long long

signed main() {

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int t;
    std::cin >> t;

    while (t--) {
        int n, a, b;
        std::cin >> n >> a >> b;
        std::pmr::vector<int> vec(2 * n + 1);
        for (int i = 1; i <= 2 * n; i++) {
            std::cin >> vec[i];
        }

        std::sort(vec.begin() + 1, vec.end());

        vec.push_back(0xffffffffffffffff);
        vec.push_back(0xffffffffffffffff);

        int idx = 1, ans = 0, not_paired = 0;

        while (idx < 2 * n) {
            if (vec[idx + 1] - vec[idx] <= a) {
                idx += 2;
            } else {
                ans = -1;
                break;
            }
        }

        if (ans == -1) {
            std::cout << "-1\n";
            continue;
        }

        idx  = 1;

        while (idx <= 2 * n) {
            if (vec[idx + 1] - vec[idx] <= b) {
                if (not_paired != 0 && vec[idx + 2] - vec[not_paired] > a) {
                    not_paired = 0;
                    idx++;
                    continue;
                }
                ans++;
                idx += 2;
            } else {
                if (not_paired == 0) {
                    not_paired = idx;
                    idx++;
                } else {
                    not_paired = 0;
                    idx++;
                }
            }
        }
        std::cout << ans << '\n';
    }
}

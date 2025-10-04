//
// Created by guanghere on 2025/10/4.
//
#include <bits/stdc++.h>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int t;
    std::cin >> t;
    while (t--) {
        int n;
        std::cout << std::flush;
        std::cin >> n;
        std::vector flag(n + 1, std::set<int>());
        std::set<int> pre;
        bool found = false;
        for (int i = 1; i <= n; ++i) {
            std::vector<int> indices;
            for (int j = 1; j <= n * n + 1; ++j) {
                if (!pre.contains(j)) {
                    indices.push_back(j);
                }
            }

            std::cout << std::flush;
            std::cout << "? " << indices.size() << " ";
            for (const auto idx: indices) {
                std::cout << idx << " ";
            }
            std::cout << std::endl;

            int k;
            std::cin >> k;
            for (int j = 1, x; j <= k; ++j) {
                std::cin >> x;
                pre.insert(x);
                flag[i].insert(x);
            }
            if (k >= n + 1) {
                std::cout << std::flush;
                std::cout << "! ";
                int cnt = 0;
                for (const auto j: flag[i]) {
                    std::cout << j << " ";
                    cnt++;
                    if (cnt == n + 1)
                        break;
                }
                std::cout << std::endl;
                found = true;
                break;
            }
        }
        if (!found) {
            std::cout << "! ";
            std::vector<int> indices;
            for (int j = n * n + 1; j >= 1; --j) {
                if (!pre.contains(j)) {
                    indices.push_back(j);
                    break;
                }
            }
            for (int i = n; i >= 1; --i) {
                auto it = flag[i].lower_bound(indices.back());
                --it;
                indices.push_back(*it);
            }
            std::ranges::reverse(indices);
            for (const auto idx: indices) {
                std::cout << idx << " ";
                std::cout << std::flush;
            }
            std::cout << std::endl;
        }
    }
}
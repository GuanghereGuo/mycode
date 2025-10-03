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
        std::vector flag(n + 1, std::vector<bool>(n * n + 2, false));
        std::vector<bool> pre(n * n + 2);
        bool found = false;
        for (int i = 1; i <= n; ++i) {
            std::vector<int> indices;
            for (int j = 1; j <= n * n + 1; ++j) {
                if (!pre[j]) {
                    indices.push_back(j);
                }
            }

            std::cout << std::flush;
            std::cout << "? " << indices.size() << " ";
            for (const auto idx: indices) {
                std::cout << idx << " ";
            }
            std::cout << std::endl;
            std::cout << std::flush;

            int k;
            std::cin >> k;
            for (int j = 1, x; j <= k; ++j) {
                std::cin >> x;
                pre[x] = flag[i][x] = true;
            }
            if (k >= n + 1) {
                std::cout << std::flush;
                std::cout << "! ";
                for (int j = 1, cnt = 0; j <= n * n + 1 && cnt <= n + 1; ++j) {
                    if (flag[1][j]) {
                        std::cout << j << " ";
                        std::cout << std::flush;
                        cnt++;
                    }
                }
                std::cout << std::endl;
                std::cout << std::flush;
                found = true;
                break;
            }
        }
        if (!found) {
            std::cout << "! ";
            std::vector<int> indices;
            for (int j = 1; j <= n * n + 1; ++j) {
                if (!pre[j]) {
                    indices.push_back(j);
                    break;
                }
            }
            for (int i = n; i >= 1; --i) {
                for (int j = n * n + 1; j >= 1; --j) {
                    if (flag[i][j]) {
                        indices.push_back(j);
                        break;
                    }
                }
                if (indices.size() == n + 1) {
                    break;
                }
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

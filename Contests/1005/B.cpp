//
// Created by 24087 on 24-10-5.
//
#include <cassert>
#include <iostream>
#include <unordered_set>
#include <vector>

#define int long long

signed main() {
    int T;
    std::cin >> T;
    while (T--) {
        int n, k, m;
        std::cin >> n >> k >> m;
        std::vector<int> favorite(n);

        for (int i = 0; i < n; ++i) {
            std::cin >> favorite[i];
        }

        std::vector<int> happiness(n, 0);
        std::unordered_set<int> pot;

        if (m <= 2 * n) {
            for (int i = 0; i < m; ++i) {
                int tourist = i % n;
                int ingredient = favorite[tourist];

                if (pot.contains(ingredient)) {
                    pot.erase(ingredient);
                    happiness[tourist]++;
                } else {
                    pot.insert(ingredient);
                }
            }
        } else {
            for (int i = 0; i < 2 * n; ++i) {
                int tourist = i % n;
                int ingredient = favorite[tourist];
                if (pot.contains(ingredient)) {
                    pot.erase(ingredient);
                    happiness[tourist]++;
                } else {
                    pot.insert(ingredient);
                }
            }
            for (int i = 0; i < n; ++i) {
                happiness[i] *= m / (2 * n);
            }
            for (int i = m / (2 * n) * 2 * n; i < m; ++i) {
                int tourist = i % n;
                int ingredient = favorite[tourist];
                if (pot.contains(ingredient)) {
                    pot.erase(ingredient);
                    happiness[tourist]++;
                } else {
                    pot.insert(ingredient);
                }
            }
        }

        for (int i = 0; i < n; ++i) {
            if (i > 0) std::cout << " ";
            std::cout << happiness[i];
        }
        if(T != 0)
            std::cout << std::endl;
    }
}

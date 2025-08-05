//
// Created by guanghere on 25-8-5.
//
#include <iostream>
#include <vector>
#include <string>
#include <numeric>

void solve() {
    int id, m, k, n;
    std::cin >> id >> m >> k >> n;

    std::string ans;
    ans.reserve(m);

    for (int i = 0; i < m; ++i) {
        bool is_damaged_set = false;
        for (int j = 0; j < k; ++j) {
            const int N = n * n;
            std::vector<int> p(N + 1);
            for (int l = 1; l <= N; ++l) {
                std::cin >> p[l];
            }

            if (is_damaged_set) {
                continue;
            }

            std::vector<bool> vis(N + 1, false);
            int cyc = 0;
            for (int l = 1; l <= N; ++l) {
                if (!vis[l]) {
                    cyc++;
                    int cur = l;
                    while (!vis[cur]) {
                        vis[cur] = true;
                        cur = p[cur];
                    }
                }
            }

            if ((N - cyc) % 2 != 0) {
                is_damaged_set = true;
            }
        }

        if (is_damaged_set) {
            ans += '1';
        } else {
            ans += '0';
        }
    }
    std::cout << ans << std::endl;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    solve();
    return 0;
}

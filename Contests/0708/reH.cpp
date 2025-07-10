//
// Created by guanghere on 25-7-9.
//
#include <bits/stdc++.h>

#define int long long

int dir[8][2] = {{0, 1},  {0, -1}, {1, 0},  {1, 1},
                 {1, -1}, {-1, 0}, {-1, 1}, {-1, -1}};

signed main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;
    while (t--) {
        int n, m, l, r;
        std::cin >> n >> m >> l >> r;

        std::vector<std::string> mp(n);
        std::vector dis(2, std::vector(n, std::vector<int>(m, LLONG_MAX)));

        for (int i = 0; i < n; i++) {
            std::cin >> mp[i];
        }

        std::queue<std::tuple<int, int, int>> q;
        q.emplace(0, 0, 0);
        dis[0][0][0] = 0;

        while (!q.empty()) {
            auto [x, y, c] = q.front();
            q.pop();
            for (int i = 0; i < 8; i++) {
                int nx = x + dir[i][0];
                int ny = y + dir[i][1];
                if (nx >= 0 && nx < n && ny >= 0 && ny < m &&
                    mp[nx][ny] == '1' && dis[1 - c][nx][ny] == LLONG_MAX) {
                    dis[1 ^ c][nx][ny] = dis[c][x][y] + 1;
                    q.emplace(nx, ny, 1 ^ c);
                }
            }
        }
        if (l != r) {
            int d = std::min(dis[0][n - 1][m - 1], dis[1][n - 1][m - 1]);
            if (d == LLONG_MAX) {
                std::cout << -1 << '\n';
            } else {
                std::cout << (d + r - 1) / r << '\n';
            }
        } else {
            int d_even = dis[0][n - 1][m - 1];
            int d_odd = dis[1][n - 1][m - 1];
            if (l % 2 == 0) {
                int k_even = (d_even + r - 1) / r;
                if (d_even != LLONG_MAX) {
                    std::cout << k_even << '\n';
                } else {
                    std::cout << -1 << '\n';
                }
            } else {
                int k = LLONG_MAX;
                if (d_odd != LLONG_MAX) {
                    k = std::min(k, (d_odd + r - 1) / r);
                    if (k % 2 == 0) {
                        k++;
                    }
                }
                if (d_even != LLONG_MAX) {
                    int kk = (d_even + r - 1) / r;
                    k = std::min(k, kk+ (kk & 1));
                }
                std::cout << (k == LLONG_MAX ? -1 : k) << '\n';
            }
        }
    }
}
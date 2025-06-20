//
// Created by guanghere on 25-4-12.
//
#include <iostream>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, m, h;
    std::cin >> n >> m >> h;
    //std::cerr << n << m << h << std::endl;
    std::vector mp(n + 1, std::vector<int>(m + 1));
    for (int i = 1, x; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            std::cin >> mp[i][j];
        }
    }
    int dir[5][2] = {{0, 0},{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    auto chk = [&](int x, int y) -> bool {
        return x < 1 || x > n || y < 1 || y > m;
    };
    int ans = 0, max_n = 0, max_i = 114, max_j = 514;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (mp[i][j]) {
                continue;
            }
            int cnt = 0;
            for (int k = 1; k <= 4; k++) {
                for (int stp = 1;; stp++) {
                    int nxt_x = i + stp * dir[k][0];
                    int nxt_y = j + stp * dir[k][1];
                    if (chk(nxt_x, nxt_y)) {
                        break;
                    }
                    if (mp[nxt_x][nxt_y] < 0) {
                        cnt++;
                    } else if (mp[nxt_x][nxt_y] >= h) {
                        break;
                    }
                }
            }
            if (cnt >= 3) {
                ans++;
            }
            if (cnt > max_n) {
                max_n = cnt;
                max_i = i;
                max_j = j;
            }
        }
    }
    std::cout << ans << '\n';
    std::cout << max_i - 1 << ' ' << max_j - 1 << '\n';
}
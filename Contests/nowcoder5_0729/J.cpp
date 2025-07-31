//
// Created by guanghere on 25-7-29.
//
#include <bits/stdc++.h>

bool check(const std::vector<std::vector<int>> &dist, int n, int m, int t) {
    long long max_sum = -3e9, min_sum = 3e9;
    long long max_diff = -3e9, min_diff = 3e9;
    bool has_problematic_cell = false;

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (dist[i][j] > t) {
                has_problematic_cell = true;
                long long current_sum = (long long)i + j;
                long long current_diff = (long long)i - j;
                max_sum = std::max(max_sum, current_sum);
                min_sum = std::min(min_sum, current_sum);
                max_diff = std::max(max_diff, current_diff);
                min_diff = std::min(min_diff, current_diff);
            }
        }
    }

    if (!has_problematic_cell) {
        return true;
    }

    long long lu = max_sum - t;
    long long ru = min_sum + t;
    long long lv = max_diff - t;
    long long rv = min_diff + t;


    if (lu > ru || lv > rv) {
        return false;
    }

    {
        long long u_even_start = lu;
        if ((u_even_start % 2 + 2) % 2 != 0) u_even_start++;

        long long v_even_start = lv;
        if ((v_even_start % 2 + 2) % 2 != 0) v_even_start++;

        if (u_even_start <= ru && v_even_start <= rv) {
            return true;
        }
    }

    {
        long long u_odd_start = lu;
        if ((u_odd_start % 2 + 2) % 2 == 0) u_odd_start++;

        long long v_odd_start = lv;
        if ((v_odd_start % 2 + 2) % 2 == 0) v_odd_start++;

        if (u_odd_start <= ru && v_odd_start <= rv) {
            return true;
        }
    }

    return false;
}


// bool check(const std::vector<std::vector<int>> &dist, int n, int m, int t) {
//
//     int a = -1e9, b = 1e9, c = -1e9, d = 1e9;
//     for (int i = 1; i <= n; ++i) {
//         for (int j = 1; j <= m; ++j) {
//             if (dist[i][j] > t) {
//                 a = std::max(a, i + j);
//                 b = std::min(b, i + j);
//                 c = std::max(c, i - j);
//                 d = std::min(d, i - j);
//             }
//         }
//     }
//     int dis = std::max(a - b, c - d);
//     return dis <= 2 * t;
// }

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;
    std::vector g(n + 1, std::vector<int>(m + 1));

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            std::cin >> g[i][j];
        }
    }

    std::queue<std::pair<int, int>> q;
    std::vector dist(n + 1, std::vector<int>(m + 1, 1e9 + 1));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (g[i][j]) {
                q.emplace(i, j);
                dist[i][j] = 0;
            }
        }
    }

    constexpr int dir[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    int cnt = 0;

    while (!q.empty()) {
        std::vector<std::pair<int, int>> v;
        while (!q.empty()) {
            auto [x, y] = q.front();
            q.pop();
            for (auto d : dir) {
                int nx = x + d[0];
                int ny = y + d[1];
                if (nx < 1 || nx > n || ny < 1 || ny > m || g[nx][ny] == 1) {
                    continue;
                }
                g[nx][ny] = 1;
                v.emplace_back(nx, ny);
            }
        }
        cnt++;
        for (auto [x, y] : v) {
            q.emplace(x, y);
            dist[x][y] = cnt;
        }
    }

    int l = 0, r = n + m;
    while (l < r) {
        const int mid = (l + r) / 2;
        if (check(dist, n, m, mid)) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }
    std::cout << l << '\n';
}
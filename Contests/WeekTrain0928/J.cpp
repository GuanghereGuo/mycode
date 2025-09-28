//
// Created by guanghere on 2025/9/28.
//
#include <bits/stdc++.h>

using ld = long double;

const ld INF = 1e18;

struct pt {
    ld x, y;
};

int n;
std::vector<pt> p;
std::vector<std::vector<ld>> dp;
std::vector<std::vector<ld>> dist;

auto solve_tsp() -> ld {
    dp.assign(1 << n, std::vector<ld>(n, INF));

    for (int i = 0; i < n; ++i) {
        dp[1 << i][i] = 0;
    }

    for (int s = 1; s < (1 << n); ++s) {
        for (int i = 0; i < n; ++i) {
            if (!((s >> i) & 1))
                continue;
            if (dp[s][i] > INF / 2)
                continue;

            for (int j = 0; j < n; ++j) {
                if (!((s >> j) & 1)) {
                    int next_s = s | (1 << j);
                    dp[next_s][j] = std::min(dp[next_s][j], dp[s][i] + dist[i][j]);
                }
            }
        }
    }

    ld min_path = INF;
    for (int i = 0; i < n; ++i) {
        min_path = std::min(min_path, dp[(1 << n) - 1][i]);
    }
    return min_path;
}

auto main() -> int {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n;
    p.resize(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> p[i].x >> p[i].y;
    }

    std::vector<ld> angles;
    angles.push_back(0);
    angles.push_back(std::numbers::pi_v<ld> / 4.0);

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            ld dx = p[j].x - p[i].x;
            ld dy = p[j].y - p[i].y;
            ld angle = atan2(dy, dx);
            angles.push_back(angle);
            angles.push_back(angle + std::numbers::pi_v<ld> / 4.0);
        }
    }

    ld min_total_dist = INF;
    dist.resize(n, std::vector<ld>(n));

    for (ld theta : angles) {
        ld c = cos(theta);
        ld s = sin(theta);

        std::vector<pt> rotated_p(n);
        for (int i = 0; i < n; ++i) {
            rotated_p[i].x = p[i].x * c + p[i].y * s;
            rotated_p[i].y = -p[i].x * s + p[i].y * c;
        }

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                dist[i][j] = std::abs(rotated_p[i].x - rotated_p[j].x) + std::abs(rotated_p[i].y - rotated_p[j].y);
            }
        }

        min_total_dist = std::min(min_total_dist, solve_tsp());
    }

    std::cout << std::fixed << std::setprecision(12) << min_total_dist << std::endl;

    return 0;
}

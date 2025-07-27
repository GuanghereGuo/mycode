//
// Created by guanghere on 25-7-24.
//
#include <bits/stdc++.h>

struct Node {
    int x, y;
    int min_y = INT_MAX;
    explicit Node(int _x, int _y, int min_y = INT_MAX) : x(_x), y(_y), min_y(min_y) {}
};

void solve() {
    int n, m, k;
    std::cin >> n >> m >> k;
    std::vector<std::string> mp(n);
    for (int i = 0; i < n; i++) {
        std::cin >> mp[i];
    }

    if (k == m - 1) {
        std::cout << "NO\n";
        return;
    }

    std::vector can_vis(n, std::vector<bool>(m));

    // rev_bfs
    {
        std::queue<std::pair<int, int>> q;
        q.emplace(0, m - 1);
        can_vis[0][m - 1] = true;
        while (!q.empty()) {
            auto [x, y] = q.front();
            q.pop();
            if (x > 0 && !can_vis[x - 1][y] && mp[x - 1][y] == '0') {
                can_vis[x - 1][y] = true;
                q.emplace(x - 1, y);
            }
            if (x < n - 1 && !can_vis[x + 1][y] && mp[x + 1][y] == '0') {
                can_vis[x + 1][y] = true;
                q.emplace(x + 1, y);
            }
            if (y > 0 && !can_vis[x][y - 1] && mp[x][y - 1] == '0') {
                can_vis[x][y - 1] = true;
                q.emplace(x, y - 1);
            }
        }
    }

    //cerr can_vis
    // for (int i = 0; i < n; i++) {
    //     for (int j = 0; j < m; j++) {
    //         std::cerr << can_vis[i][j] << " \n"[j == m - 1];
    //     }
    // }

    // bfs
    {
        std::queue<Node> q;
        q.emplace(0, 0);
        std::vector vis(n, std::vector<bool>(m));
        vis[0][0] = true;
        bool flag = true;
        while (!q.empty()) {
            auto [x, y, cant_vis] = q.front();
            q.pop();
            if (cant_vis != INT_MAX && cant_vis + k <= y && cant_vis + k != m - 1) {
                std::cout << "YES\n";
                flag = false;
                break;
            }
            if (x < n - 1 && !vis[x + 1][y] && mp[x + 1][y] == '0') {
                vis[x + 1][y] = true;
                if (!can_vis[x + 1][y] || cant_vis != INT_MAX) {
                    q.emplace(x + 1, y, std::min(cant_vis, y));
                } else {
                    q.emplace(x + 1, y);
                }
            }
            if (x > 0 && !vis[x - 1][y] && mp[x - 1][y] == '0') {
                vis[x - 1][y] = true;
                if (!can_vis[x - 1][y] || cant_vis != INT_MAX) {
                    q.emplace(x - 1, y, std::min(cant_vis, y));
                } else {
                    q.emplace(x - 1, y);
                }
            }
            if (y < m - 1 && !vis[x][y + 1] && mp[x][y + 1] == '0') {
                vis[x][y + 1] = true;
                if (!can_vis[x][y + 1] || cant_vis != INT_MAX) {
                    q.emplace(x, y + 1, std::min(cant_vis, y));
                } else {
                    q.emplace(x, y + 1);
                }
            }
        }
        if (flag) {
            std::cout << "NO\n";
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}

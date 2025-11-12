//
// Created by guanghere on 2025/11/12.
//
//
// Created by guanghere on 2025/11/12.
//
#include <bits/stdc++.h>

struct Node {
    int i = 0, eta = 0;
    bool t_stop = false;

    bool operator<(const Node& other) const {
        return eta > other.eta;
    }
};

signed main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;
    std::vector<int> t(n + 1), a(n + 1), dir(n + 1);// left = -1 right = 1
    std::vector<std::vector<int>> pursuers(n + 1);
    std::priority_queue<Node> q;
    for (int i = 1; i <= n; ++i) {
        std::cin >> t[i];
        pursuers[t[i]].push_back(i);
    }
    for (int i = 1; i <= n; ++i) {
        std::cin >> a[i];
    }
    for (int i = 1; i <= n; ++i) {
        if (a[t[i]] > a[i]) {
            dir[i] = 1;
        } else {
            dir[i] = -1;
        }
    }
    for (int i = 1; i <= n; ++i) {
        if (dir[i] * dir[t[i]] == -1) {
            q.push({i, std::abs(a[i] - a[t[i]]), false});
        }
    }

    std::vector<int> ans(n + 1);
    std::vector<bool> stop(n + 1, false);
    while (!q.empty()) {
        auto [idx, eta, tar_stop] = q.top();
        q.pop();
        if (stop[idx])
            continue;
        if (stop[t[idx]] && !tar_stop) {
            continue;
        }
        stop[idx] = true;
        ans[idx] = eta;
        for (int i : pursuers[idx]) {
            if (stop[i])
                continue;
            if (dir[i] * dir[t[i]] == -1)
                q.push({i, std::abs(a[i] - a[t[i]]) * 2 - eta, true});
            else
                q.push({i, std::abs(a[i] - a[t[i]]) * 2 + eta, true});
        }
    }

    for (int i = 1; i <= n; ++i) {
        std::cout << ans[i] << " ";
    }
    std::cout << "\n";

}
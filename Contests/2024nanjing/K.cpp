//
// Created by guanghere on 2025/10/5.
//
#include <bits/stdc++.h>

void solve() {
    int n, m, k, w;
    std::cin >> n >> m >> k >> w;
    std::vector<int> a, b;
    std::vector<std::vector<int>> g;
    for (int i = 1, x; i <= n; i++) {
        std::cin >> x;
        a.push_back(x);
    }
    for (int i = 1, x; i <= m; i++) {
        std::cin >> x;
        b.push_back(x);
    }
    std::sort(a.begin(), a.end());
    std::sort(b.begin(), b.end());
    //fen qu
    int pre = 0;
    std::vector<int> pres;
    for (auto i : b) {
        if (i - 1 == pre) {
            pre = i;
            continue;
        }
        g.emplace_back(1, i - 1 - pre);
        auto &cur = g.back();
        int l = pre + 1, r = i - 1;
        pres.push_back(pre);
        auto it1 = std::lower_bound(a.begin(), a.end(), l);
        auto it2 = std::upper_bound(a.begin(), a.end(), r);
        for (; it1 != it2; ++it1) {
            cur.push_back(*it1 - pre);
        }
        pre = i;
    }
    if (pre < w) {
        g.emplace_back(1, w - pre);
        auto &cur = g.back();
        int l = pre + 1, r = w;
        auto it1 = std::lower_bound(a.begin(), a.end(), l);
        auto it2 = std::upper_bound(a.begin(), a.end(), r);
        for (; it1 != it2; ++it1) {
            cur.push_back(*it1 - pre);
        }
        pres.push_back(pre);
    }

    // yu chu li
    std::vector<int> cand;
    int ans = 0;
    for (auto &cur : g) {
        if (cur.size() <= 1) {
            continue;
        }
        int len = cur[0];
        int now = cur[1];

        cand.push_back(now + pres[&cur - &g[0]]);
        int cnt = 1;
        while (now <= len) {
            auto it = std::upper_bound(cur.begin() + 1, cur.end(), now + k - 1);
            if (it != cur.end()) {
                now = *it;
                cnt++;
                cand.push_back(now + pres[&cur - &g[0]]);
            } else {
                break;
            }
        }
        if (k * cnt > len) {
            std::cout << -1 << "\n";
            return;
        }

        int end = len + pres[&cur - &g[0]];
        auto it = cand.end() - 1;
        while (*it + k - 1 > end) {
            *it = end - k + 1;
            end = *it - 1;
            if (it == cand.begin()) break;
            it--;
        }
        ans += cnt;
    }
    std::cout << ans << '\n';
    for (int i = 0; i < ans; i++) {
        std::cout << cand[i] << ' ';
    }
    std::cout << '\n';
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }
}
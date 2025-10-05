//
// Created by guanghere on 2025/10/5.
//
#include <bits/stdc++.h>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;

    while (t--) {
        int n, m, k, ans = 0;
        std::cin >> n >> m >> k;
        std::vector friends(k + 1, false);
        std::vector<std::pair<int, int>> val(k + 1);
        for (int i = 1; i <= k; ++i) {
            val[i].second = i;
        }
        std::map<std::pair<int, int>, int> mp;
        for (int i = 0, x; i < n; ++i) {
            std::cin >> x;
            friends[x] = true;
        }
        for (int i = 1, x, y; i <= m; i++) {
            std::cin >> x >> y;
            if (x == y) {
                if (friends[x]) {
                    ans++;
                } else {
                    val[x].first++;
                }
            } else if (friends[x] && friends[y]) {
                ans++;
            } else if (friends[x]) {
                val[y].first++;
            } else if (friends[y]) {
                val[x].first++;
            } else {
                if (x > y) std::swap(x, y);
                mp[{x, y}]++;
            }
        }


        auto tmp = val;
        std::sort(tmp.begin(), tmp.end(), std::greater());
        int sum = tmp[1].first + tmp[0].first;
        // int x = val[0].second, y = val[1].second;
        // if (x > y) std::swap(x, y);
        // if (mp.count({x, y})) {
        //     sum += mp[{x, y}];
        // }

        for (const auto& [_, cnt] : mp) {
            sum = std::max(sum, cnt + val[_.first].first + val[_.second].first);
        }
        std::cout << ans + sum << "\n";
    }

}
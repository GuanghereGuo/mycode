//
// Created by 24087 on 9/11/2024.
//
#include <algorithm>
#include <climits>
#include <iostream>
#include <map>
#include <vector>

//#define int long long

class Solution {
    int n = 0;
    std::vector<std::pair<int, int>> v_w_sorted;
    std::vector<std::pair<int, int>> w_sorted;

    [[nodiscard]] bool check(const int mid) const {
        std::vector<int> to_help, can_help;
        for (int i = 0; i < n; i++) {
            if (w_sorted[i].second < mid)
                to_help.emplace_back(w_sorted[i].first);
            if (v_w_sorted[i].second >= mid)
                can_help.emplace_back(v_w_sorted[i].first +
                                      v_w_sorted[i].second);
        }
        if (to_help.size() > can_help.size())
            return false;
        for (int i = 0; i < to_help.size(); i++) {
            if (can_help[i] - to_help[i] < mid)
                return false;
        }
        return true;
    }

  public:
    Solution() {
        std::cin >> n;
        int l = INT_MAX, r = 0;
        for (int i = 0; i < n; i++) {
            int v, w;
            std::cin >> v >> w;
            v_w_sorted.emplace_back(w, v);
            r = std::max(r, v);
            l = std::min(l, v);
        }
        r++;

        w_sorted = v_w_sorted;

        std::ranges::sort(v_w_sorted,
                          [](const std::pair<int, int> &a,
                             const std::pair<int, int> &b) -> bool {
                              return a.first + a.second > b.first + b.second;
                          });
        std::ranges::sort(w_sorted, std::greater<>());

        while (l + 1 < r) {
            if (const int mid = (l + r) / 2; check(mid)) {
                l = mid;
            } else {
                r = mid;
            }
        }

        std::cout << l << '\n';
    }
};

signed main() {
    std::ios::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;
    while (t--) {
        Solution ans;
    }
}

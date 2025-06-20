//
// Created by 24087 on 24-10-13.
//
#include <algorithm>
#include <iostream>
#include <vector>

#define int long long

struct Contest {
    int s, sum, num, ans, id;  // num of -1
    Contest() = default;
    Contest(int s, int sum, int num, int id)
        : s(s), sum(sum), num(num), ans(sum), id(id) {}
};

class Solution {
    int n, k;
    std::vector<Contest> contests;
    std::vector<std::vector<int>> information;

    std::vector<int> calculate(const std::vector<int> &ori, int sum, int ans) {
        std::vector<int> ret;
        int diff = ans - sum;
        for (int i : ori) {
            if (i == -1) {
                int to_fill = k <= diff ? k : diff;
                diff -= to_fill;
                ret.push_back(to_fill);
            } else {
                ret.push_back(i);
            }
        }
        return ret;
    }

   public:
    Solution(int n, int k, std::vector<Contest> &&contests,
             std::vector<std::vector<int>> &&information)
        : n(n), k(k), contests(contests), information(information) {}
    void print_ans() {
        std::sort(contests.begin(), contests.end(),
                  [](const Contest &a, const Contest &b) { return a.s < b.s; });
        std::vector<std::pair<std::vector<int>, int>> ans;
        ans.emplace_back(calculate(information[contests[0].id], contests[0].sum,
                                   contests[0].sum),
                         contests[0].id);
        int pre_max_ans = -1;
        int now_max_ans = contests[0].ans;
        for (int i = 1; i < n; i++) {
            if(contests[i].s != contests[i - 1].s) {
                pre_max_ans = now_max_ans;
            }
            int now_sum = contests[i].sum;
            int now_num = contests[i].num;
            if (now_sum <= pre_max_ans) {
                if (now_sum + now_num * k <= pre_max_ans) {
                    std::cout << "No\n";
                    return;
                }
                contests[i].ans = pre_max_ans + 1;
            }
            ans.emplace_back(calculate(information[contests[i].id], now_sum,
                                       contests[i].ans),
                             contests[i].id);
            now_max_ans = std::max(now_max_ans, contests[i].ans);
        }
        std::cout << "Yes\n";
        std::sort(ans.begin(), ans.end(),
                  [](const std::pair<std::vector<int>, int> &a,
                     const std::pair<std::vector<int>, int> &b) {
                      return a.second < b.second;
                  });
        for (const auto &[i, id] : ans) {
            for (int j : i) {
                std::cout << j << ' ';
            }
            std::cout << '\n';
        }
    }
};

signed main() {
    int t;
    std::cin >> t;
    while (t--) {
        int n, m, k;
        std::cin >> n >> m >> k;
        std::vector<Contest> contests;
        std::vector<std::vector<int>> information;
        for (int i = 0; i < n; i++) {
            int sum = 0, num = 0, s;
            std::cin >> s;
            std::vector<int> vec;
            for (int j = 1, x; j <= m; j++) {
                std::cin >> x;
                vec.push_back(x);
                if (x == -1) {
                    num++;
                } else {
                    sum += x;
                }
            }
            contests.emplace_back(s, sum, num, i);
            information.push_back(std::move(vec));
        }
        Solution ans(n, k, std::move(contests), std::move(information));
        ans.print_ans();
    }
}
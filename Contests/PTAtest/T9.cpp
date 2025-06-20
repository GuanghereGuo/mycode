//
// Created by guanghere on 25-4-12.
//
#include <iostream>
#include <stack>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, m, s, opt;
    std::cin >> n >> m >> s;
    std::vector<std::stack<char>> stk(n + 1);
    std::vector<char> ans;
    for (int i = 1; i <= n; i++) {
        std::string str;
        std::cin >> str;
        for (int j = m - 1; j >= 0; j--) {
            stk[i].push(str[j]);
        }
    }
    std::cin >> opt;
    while (opt != -1) {
        auto opt0 = [&]() {
            if (!stk[0].empty()) {
                auto c = stk[0].top();
                stk[0].pop();
                ans.push_back(c);
            }
        };
        if (opt == 0) {
            opt0();
        } else {
            if (stk[opt].empty()) {
                std::cin >> opt;
                continue;
            }
            auto c = stk[opt].top();
            stk[opt].pop();
            if (stk[0].size() >= s) {
                opt0();
            }
            stk[0].push(c);
        }
        std::cin >> opt;
    }
    for (int i = 0; i < (int)ans.size(); i++) {
        std::cout << ans[i];
    }
}
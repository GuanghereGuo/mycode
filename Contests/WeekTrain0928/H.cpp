//
// Created by guanghere on 2025/9/28.
//
#include <bits/stdc++.h>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;
    if (n == 1) {
        std::cin >> n;
        std::cout << n;
        return 0;
    }
    std::vector<int> vec(n + 1);
    std::multimap<long long, std::string> q;
    for (int i = 1; i <= n; i++) {
        std::cin >> vec[i];
        q.insert({vec[i], std::to_string(vec[i])});
    }

    while (!q.empty()) {
        auto it = q.begin();
        auto [val, expr]= *it;
        if (val == 1) {
            q.erase(it);
            it = q.find(2);
            if (it != q.end()) {
                auto [v2, e2] = *it;
                q.erase(it);
                q.insert({3, "(1+" + e2 + ")"});
            } else {
                it = q.begin();
                if (it != q.end()) {
                    auto [v2, e2] = *it;
                    q.erase(it);
                    q.insert({v2 + 1, "(1+" + e2 + ")"});
                }
            }
        } else {
            break;
        }
    }
    auto it = q.begin();
    auto [val, expr]= *it;
    q.erase(it);
    std::cout << expr;
    while (!q.empty()) {
        it = q.begin();
        auto [val, expr]= *it;
        q.erase(it);
        std::cout << "*" << expr;
    }
}
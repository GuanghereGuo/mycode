//
// Created by guanghere on 25-7-10.
//
#include <bits/stdc++.h>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;
    while (t--) {
        int n;
        bool flag = false;
        std::string s;
        std::cin >> n >> s;
        if (s[0] != s[n - 1]) {
            std::cout << "empty\n";
            continue;
        }
        for (int i = 1; i < n; i++) {
            if (s[i - 1] == s[i] && s[i] != s[0]) {
                std::cout << "empty\n";
                flag = true;
                break;
            }
        }
        if (flag) continue;
        char target = s[n - 1];
        int min_len = INT_MAX;
        int now_len = 0;
        bool has = false;

        for (char c : s) {
            if (c == target) {
                now_len++;
                has = true;
            } else {
                if (now_len > 0) {
                    min_len = std::min(min_len, now_len);
                }
                now_len = 0;
            }
        }
        if (now_len > 0) {
            min_len = std::min(min_len, now_len);
        }
        if (has) {
            std::cout << std::string(min_len, target) << '\n';
        } else {
            std::cout << s << '\n';
        }
    }
}
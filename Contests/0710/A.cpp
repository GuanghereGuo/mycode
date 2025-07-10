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
        int first_idx = -1, last_idx = -1;
        for (int i = 1; i < n; i++) {
            if (first_idx == -1 && s[i] != s[0]) {
                first_idx = i;
            }
            if (s[i - 1] == s[i] && s[i] != s[0]) {
                std::cout << "empty\n";
                flag = true;
                break;
            }
        }
        if (flag) continue;
        for (int i = n - 2; i >= 0; i--) {
            if (s[i] != s[n - 1]) {
                last_idx = i;
                break;
            }
        }
        if (first_idx == -1 || last_idx == -1) {
            std::cout << s << '\n';
        } else {
            if (first_idx < n - last_idx - 1) {
                std::cout << s.substr(0, first_idx) << '\n';
            } else {
                std::cout << s.substr(last_idx + 1) << '\n';
            }
        }
    }
}
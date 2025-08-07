//
// Created by guanghere on 25-8-7.
//
#include <bits/stdc++.h>

void solve() {
    std::string s;
    std::cin >> s;
    if (s[0] == '-') {
        int n = s.size();
        int pos = -1;
        for (int i = 1; i < n; ++i) {
            if (s[i] > '1') {
                pos = i;
                break;
            }
        }
        if (pos != -1) {
            s.insert(pos, "1");
        } else {
            s.push_back('1');
        }
    } else {
        size_t pos = s.find('0');
        if (pos != std::string::npos) {
            s.insert(pos, "1");
        } else {
            s.push_back('1');
        }
    }
    std::cout << s << '\n';
}
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
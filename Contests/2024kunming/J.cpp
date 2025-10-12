//
// Created by guanghere on 2025/10/12.
//
#include <bits/stdc++.h>

void solve() {
    int n;
    std::string s;
    std::cin >> n >> s;
    std::vector<int> vec(n + 1);
    int cnt = 0;
    for (int i = 1; i <= n; ++i) {
        std::cin >> vec[i];
        if (vec[i] != i) {
            cnt++;
        }
    }
    if (n == 2) {
        std::cout << "Alice\n";
    } else if (n == 3 && s == "Bob" && (cnt == 3)) {
        std::cout << "Alice\n";
    } else if (s == "Bob" && cnt == 0) {
        std::cout << "Alice\n";
    } else if (s == "Bob" && cnt == 0) {
        std::cout << "Alice\n";
    } else if (cnt == 2 && s == "Alice") {
        std::cout << "Alice\n";
    } else {
        std::cout << "Bob\n";
    }
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
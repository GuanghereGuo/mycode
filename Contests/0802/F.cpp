//
// Created by guanghere on 25-8-2.
//
#include <bits/stdc++.h>

int main() {
    int n;
    std::string s;
    std::cin >> n >> s;
    long long cnt = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (s[i] == 'e' && s[j] == 'f') {
                cnt += j - i;
            }
        }
    }
    std::cout << cnt << std::endl;
}
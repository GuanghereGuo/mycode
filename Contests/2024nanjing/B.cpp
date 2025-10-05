//
// Created by guanghere on 2025/10/5.
//
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        string s;
        cin >> s;
        std::vector<int> odd(3), even(3);
        for (int i = 0; i < s.size(); ++i) {
            if (i & 1) {
                odd[s[i] - '0']++;
            } else {
                even[s[i] - '0']++;
            }
        }
        for (int i = 0; i < 2; ++i) {
            int tmp = std::min(odd[i], even[i]);
            odd[i] -= tmp;
            even[i] -= tmp;
        }
        std::cout << std::max(int(s.size() & 1), odd[0] + odd[1] - odd[2] + even[0] + even[1] - even[2]) << '\n';
    }
    return 0;
}
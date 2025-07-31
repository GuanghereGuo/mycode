//
// Created by guanghere on 25-7-27.
//
#include <bits/stdc++.h>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;

    while (t--) {
        int n, c;
        std::cin >> n >> c;
        std::vector<int> a(n);
        for (int i = 0; i < n; ++i) {
            std::cin >> a[i];
            a[i] = static_cast<int>(c >= a[i] ? std::log2(1.0 * c / a[i]) : -1);
            //std::cerr << a[i] << ' ';
        }
        //std::cerr << '\n';
        std::multiset<int> s(a.begin(), a.end());
        int cnt = 0;
        while (1) {
            auto it = s.lower_bound(cnt);
            if (it != s.end()) {
                s.erase(it);
                cnt++;
            } else {
                break;
            }
        }
        std::cout << n - cnt << '\n';
    }
}
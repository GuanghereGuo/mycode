//
// Created by guanghere on 25-3-30.
//
#include <algorithm>
#include <iostream>
#include <vector>

using ll = long long;

signed main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    ll R;
    std::cin >> R;
    int n;
    std::cin >> n;
    std::vector<ll> vec(n + 1), dp1(n + 1), dp2(n + 1);
    for (int i = 1; i <= n; i++) {
        std::cin >> vec[i];
    }
    int idx = 0, flag = -1;
    for (int i = 1; i <= n; i++) {
        dp1[i] = std::max(0ll, dp1[i - 1]) + vec[i];
        dp2[i] = std::min(0ll, dp2[i - 1]) + vec[i];
        if (dp1[i] >= R) {
            idx = i;
            flag = 1;
            break;
        }
        if (dp2[i] <= -R) {
            idx = i;
            flag = 0;
            break;
        }
    }
    if (flag == -1) {
        std::cout << "uncertain\n";
        return 0;
    }
    ll now = flag * R;
    for (int i = idx + 1; i <= n; i++) {
        now += vec[i];
        now = std::max(now, 0ll);
        now = std::min(now, R);
    }
    std::cout << now;
}
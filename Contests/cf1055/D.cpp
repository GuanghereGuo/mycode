//
// Created by guanghere on 2025/10/3.
//
#include <bits/stdc++.h>

int cal(int x) {
    int cnt = 0;
    while (x > 1) {
        cnt++;
        x /= 2;
        if (x > 1) {
            x++;
        }
    }
    return cnt;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;
    while (t--) {
        int n, q;
        std::cin >> n >> q;
        std::vector<int> vec(n + 1), pre1(n + 1), pre2(n + 1);
        for (int i = 1; i <= n; ++i) {
            std::cin >> vec[i];
            pre1[i] = pre1[i - 1] + cal(vec[i]);
            pre2[i] = pre2[i - 1] + (vec[i] >= 3 && ((vec[i] - 2) & (vec[i] - 1)) == 0);// bit: 1000...001
        }
        for (int ii = 1; ii <= q; ++ii) {
            int l, r;
            std::cin >> l >> r;
            int sum1 = pre1[r] - pre1[l - 1];
            int sum2 = pre2[r] - pre2[l - 1];
            std::cout << sum1 + sum2 / 2 << "\n";
        }
    }
}

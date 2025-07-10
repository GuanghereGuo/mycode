//
// Created by guanghere on 25-7-8.
//
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int t;
    cin >> t;

    while (t--) {
        int n;
        std::cin >> n;
        int minn, maxn, cnt = 1, cnt_min = 1, cnt_max = 1;  // different numbers
        std::cin >> minn;
        std::cout << 2 * (maxn = minn) << ' ';
        for (int i = 2, x; i <= n; i++) {
            std::cin >> x;
            if (x != minn && x != maxn) {
                cnt++;
            }
            if (x == maxn) {
                cnt_max++;
            }
            if (x == minn) {
                cnt_min++;
            }
            if (x < minn) {
                minn = x;
                cnt_min = 1;
            }
            if (x > maxn) {
                maxn = x;
                cnt_max = 1;
            }
            if (cnt == 2 && cnt_min == 1 && cnt_max >= 1) {
                std::cout << 2 * maxn << ' ';
            } else {
                std::cout << maxn + minn << ' ';
            }
        }
        std::cout << '\n';
    }
}
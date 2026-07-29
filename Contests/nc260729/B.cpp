//
// Created by guanghere on 2026/7/29.
//
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        long long p;
        cin >> p;

        auto root = static_cast<long long>(sqrtl(p));
        // while ((root + 1) * (root + 1) <= p) {
        //     ++root;
        // }
        // while (root * root > p) {
        //     --root;
        // }

        auto x1 = root + 2;
        if (x1 % p == 0) {
            ++x1;
        }

        const auto x2 = x1 % p;
        const auto q = x1 * x1 - p;
        cout << x1 << ' ' << x2 << ' ' << q << '\n';
    }
}

#include <bits/stdc++.h>

#define int long long

void solve() {
    int n;
    std::cin >> n;
    std::vector<int> vec(n + 1);
    for (int i = 1; i <= n; ++i) {
        std::cin >> vec[i];
    }
    sort(vec.begin() + 1, vec.end(), std::greater<>());
    std::vector<int> pre(n + 1);
    for (int i = 1; i <= n; ++i) {
        pre[i] = pre[i - 1] + vec[i];
    }
    for (int k = 1; k <= n; k++) {
        if (k == 1 || k == 2) {
            std::cout << 0 << " ";
            continue;
        }
        int s1 = 1, s2 = k;
        int c = pre[k] - pre[0];
        while (s2 <= n && vec[s1] * 2 >= c) {
            s1++, s2++;
            c = pre[s2] - pre[s1 - 1];
        }
        if (s2 == n + 1) {
            std::cout << 0 << " ";
        } else {
            std::cout << c << " ";
        }
    }
    std::cout << '\n';
}

signed main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int t;
    std::cin >> t;

    while (t--) {
        solve();
    }
}
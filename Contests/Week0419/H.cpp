//
// Created by guanghere on 2026/4/19.
//
#include <bits/stdc++.h>

#define int long long

int get_max(std::priority_queue<int> &q) {
    if (q.empty()) {
        return 0;
    }
    return q.top();
}

signed main() {

    int n;
    std::cin >> n;

    std::vector<int> t(n + 1);
    std::vector<int> a(n + 1);

    for (int i = 1; i <= n; i++) {
        std::cin >> t[i];
        if (t[i] < i) {
            std::cout << "-1\n";
            return 0;
        }
    }
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i];
    }
    std::priority_queue<int> q;
    int ans = 0;
    for (int i = n; i > 0; i--) {
        if (t[i] != t[i - 1]) {
            ans += std::max(a[i], get_max(q));
            int max_pop = t[i] - t[i - 1] - 1;
            while (!q.empty() && max_pop--) {
                ans += q.top();
                q.pop();
            }
        } else {
            q.push(std::max(a[i], get_max(q)));
        }
    }
    std::cout << ans << std::endl;
}
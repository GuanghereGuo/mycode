//
// Created by guanghere on 25-3-30.
//
#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

int main() {
    int n, k;
    std::cin >> n >> k;
    std::vector<int> d(n);
    for (int i = 0; i < n; i++) {
        std::cin >> d[i];
    }
    std::vector<std::pair<int, int>> a(n);
    for (int i = 0; i < n; i++) {
        a[i] = {d[i], i};
    }
    std::sort(a.begin(), a.end());
    std::vector<int> b(n);
    for (int i = 0; i < n; i++) {
        b[i] = a[i].first;
    }
    std::vector<long long> s(n + 1, 0), s2(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        s[i] = s[i - 1] + b[i - 1];
        s2[i] = s2[i - 1] + (long long)b[i - 1] * b[i - 1];
    }
    const long long inf = 1e18;
    std::vector f(n + 1, std::vector(k + 1, inf));
    std::vector p(n + 1, std::vector(k + 1, -1));
    f[0][0] = 0;
    for (int i = 1; i <= k; i++) {
        f[0][i] = 0;
    }
    for (int i = 1; i <= k; i++) {
        for (int j = 1; j <= n; j++) {
            for (int l = 0; l < j; l++) {
                long long cost = (j - l) * (long long)b[j - 1] * b[j - 1] -
                                 2LL * b[j - 1] * (s[j] - s[l]) +
                                 (s2[j] - s2[l]);
                long long val = f[l][i - 1] + cost;
                if (val < f[j][i]) {
                    f[j][i] = val;
                    p[j][i] = l;
                }
            }
        }
    }
    std::vector<int> t(n);
    int m = n;
    int x = k;
    while (x > 0 && m > 0) {
        int l = p[m][x];
        if (l == -1) break;
        int y = b[m - 1];
        for (int i = l; i < m; i++) {
            t[i] = y;
        }
        m = l;
        x--;
    }
    std::vector<int> ans(n);
    for (int i = 0; i < n; i++) {
        ans[a[i].second] = t[i];
    }
    for (int i = 0; i < n; i++) {
        std::cout << ans[i] << " ";
    }
    std::cout << std::endl;
    return 0;
}
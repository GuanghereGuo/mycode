//
// Created by guanghere on 2025/9/28.
//
#include <bits/stdc++.h>

void add(std::vector<int> &x, std::vector<int> &y) {
    for (int i = 0; i < 24; ++i) {
        x[i] += y[i];
    }
}

int d, h, ans = 0;
std::vector<std::vector<int>> a(7, std::vector<int>(24));

std::vector<int> stk(8);
void dfs(int q) {
    if (q == d) {
        std::vector<int> sum(24);
        for (int i = 1; i <= d; i++) {
            add(sum, a[stk[i] - 1]);
        }
        std::sort(sum.begin(), sum.end(), std::greater<int>());
        int ret = 0;
        for (int i = 0; i < h; i++) {
            ret += sum[i];
        }
        ans = std::max(ret, ans);
        return;
    }
    for (int i = stk[q] + 1; i <= 7; i++) {
        stk[q + 1] = i;
        dfs(q + 1);
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::string s[24];
    for (int i = 0; i < 7; ++i) {
        std::cin >> s[i];
    }
    std::cin >> d >> h;
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 24; j++) {
            a[i][j] = (s[i][j] == '.');
        }
    }

    dfs(0);

    std::cout << std::fixed << std::setprecision(10) << 1.0 * ans / (d * h);
}

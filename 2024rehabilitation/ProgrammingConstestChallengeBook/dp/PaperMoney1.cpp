//
// Created by 24087 on 9/4/2024.
//
#include <iostream>
#include <iterator>
#include <vector>
#include <climits>

std::vector<int> a;
int n, w, ans = INT_MAX;

void dfs(const int dep, const int sum) {
    if (sum > w) {
        return;
    }
    if (sum == w) {
        ans = std::min(ans, dep);
        return;
    }
    for (const int val : a) {
        dfs(dep + 1, sum + val);
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    std::cin >> n >> w;
    a.resize(n);

    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    dfs(0, 0);
    std::cout << ans;
}

#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, m, k;
    std::cin >> n >> m;

    std::vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i];
    }
    std::cin >> k;

    std::vector<long long> prefix_profit(n + 1, 0);
    for (int i = 1; i < n; i++) {
        prefix_profit[i + 1] = prefix_profit[i] + std::max(0, a[i + 1] - a[i]);
    }

    for (int i = 0; i < m; i++) {
        int s, t;
        std::cin >> s >> t;
        long long profit = prefix_profit[t] - prefix_profit[s];
        std::cout << k + profit << '\n';
    }

    return 0;
}
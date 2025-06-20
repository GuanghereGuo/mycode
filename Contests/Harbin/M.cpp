//
// Created by 24087 on 24-11-5.
//
#include <iostream>
#include <functional>
#include <vector>

long long cal(int n) {
    long long ans = 0;
    std::vector<int> divisors;
    for (int i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            divisors.push_back(i);
            if (i * i != n) {
                divisors.push_back(n / i);
            }
        }
    }
    std::sort(divisors.begin(), divisors.end());
    int pre = n + 1;
    for(auto it = divisors.rbegin(); it != divisors.rend(); ++it) {
        ans += 1ll * (pre - *it) * (n / *it);
        pre = *it;
    }
    return ans;
}

signed main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int t;
    std::cin >> t;
    while (t--) {
        int n;
        std::cin >> n;
        std::cout << cal(n) << std::endl;
    }
}
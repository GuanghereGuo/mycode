//
// Created by 24087 on 24-10-3.
//
//
// Created by 24087 on 24-10-3.
//
#include <iostream>


#define int long long

signed main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int T;
    std::cin >> T;

    while (T--) {
        int n, x, t;
        std::cin >> n >> x >> t;
        if(x - (2 * n - 2) * t >= t) {
            std::cout << (4 * n + 1) * t + std::max((x - 2 * n * t), 0ll) << '\n';
        } else if (x <= (2 * n - 2) * t)
            std::cout << 4 * n * t << '\n';
        else
            std::cout << 4 * n * t + (x - (2 * n - 2) * t) << '\n';
    }
}

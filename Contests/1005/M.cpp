//
// Created by 24087 on 24-10-5.
//
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    // 输入
    int n, k, x;
    cin >> n >> k >> x;

    std::vector<int> s(n + 1), t(n + 1), p(n + 1);
    std::cin >> p[0];

    for (int i = 1; i <= n; i++) {
        std::cin >> s[i];
    }
    for (int i = 1; i <= k; i++) {
        std::cin >> t[i];
    }
    for (int i = 1; i <= k; i++) {
        std::cin >> p[i];
    }

    std::sort(s.begin() + 1, s.end(), std::greater<>());

    auto check = [&](int mid) -> bool {
        int speed = s[mid];
        for (int i = 0; i <= k; i++) {
            if (static_cast<long long>(p[i] - t[i]) * speed >= x) {
                return true;
            }
        }
        return false;
    };

    int l = 0, r = n + 1;
    while (l + 1 < r) {
        int mid = (l + r) / 2;
        if (check(mid)) {
            l = mid;
        } else {
            r = mid;
        }
    }
    std::cout << l;
    // for(int i = 1; i <= n; i++) {
    //     std::cout << check(i) << ' ';
    // }
}

// 4 3 10 4
//  1 5 2 1
//  3 4 5
//  7 9 10
#include <iostream>
#include <vector>
#include <algorithm>

#define int long long

struct node {
    int a, b, c;
    bool operator<(const node& x) const { return c > x.c; }
};

signed main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t;
    std::cin >> t;

    while (t--) {
        int n, x;
        __int128 sum = 0;
        std::cin >> n >> x;
        std::vector<node> vec(n + 1);

        for (int i = 1; i <= n; i++) {
            std::cin >> vec[i].a;
            vec[i].b = vec[i].a / x;
            vec[i].c = vec[i].a % x;
            sum = sum + vec[i].b;
        }
        if (x == 1) {
            int ans = sum % 998244353;
            std::cout << ans << '\n';
            continue;
        }
        std::sort(vec.begin() + 1, vec.end());
        for (int i = 1; i <= n; i++) {
            if (sum >= x - 1 - vec[i].c) {
                sum -= x - 1 - vec[i].c;
                vec[i].c = x - 1;
            } else {
                break;
            }
        }
        int ans = sum % (x - 1);
        for (int i = 1; i <= n; i++) {
            if (vec[i].c == x - 1)
                continue;
            ans += vec[i].c;
        }
        std::cout << ans % 998244353 << '\n';
    }
}
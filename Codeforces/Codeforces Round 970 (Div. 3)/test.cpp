#pragma GCC optimize(3)
#include <cmath>
#include <bitset>
#include <iostream>
using namespace std;
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0), std::cout.tie(0);
    int t, n;
    cin >> t;
    bitset<2 * 200000> mp;
    while (t--) {
        cin >> n;
        mp.reset();
        cin >> mp;
        int sq = sqrt(n);
        if (sq * sq == n) {
            // 校验1
            int cnt = 0;
            for (int i = 0; i < n; i++) {
                if (mp.test(i)) cnt++;
            }
            if (cnt == sq * 2 + (sq - 2) * 2) {
                printf("YES\n");
            } else
                printf("NO\n");
        } else
            printf("NO\n");
    }
    return 0;
}

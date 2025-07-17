//
// Created by guanghere on 25-7-17.
//
#include <bits/stdc++.h>
using namespace std;

#define int long long

const int MOD = 998244353;
const int MAXN = 500010;

vector<int> find_cycles(int n, vector<int>& a) {
    vector visited(n, false);
    vector<int> cycles;
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            int size = 0;
            int j = i;
            while (!visited[j]) {
                visited[j] = true;
                j = a[j];
                size++;
            }
            cycles.push_back(size);
        }
    }
    return cycles;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            a[i]--;  // 转换为 0-based
        }

        vector<int> cycles = find_cycles(n, a);

        int odd_count = 0;
        vector<int> odd_sizes;
        for (int s : cycles) {
            if (s % 2 == 1) {
                odd_count++;
                odd_sizes.push_back(s);
            }
        }

        if (odd_count != 0 && odd_count != 2) {
            std::cout << 0 << std::endl;  // 不满足条件
        } else if (odd_count == 2) {
            //std::cerr << T << " odd_count == 2, sizes: ";
            long long ans = 1;
            long long s1 = odd_sizes[0];
            long long s2 = odd_sizes[1];
            for (int siz : cycles) {
                if (siz != 2 && siz % 2 == 0) {
                    ans = (ans * 2) % MOD;  // 计算偶数环的贡献
                }
            }
            ans = ans * s1 % MOD * s2 % MOD;
            std::cout << ans << std::endl;
        } else {
            long long ans = 0;
            long long tmp = 1;
            for (int siz : cycles) {
                //std::cerr << siz << ' ';
                if (siz != 2 && siz % 2 == 0) {
                    tmp = (tmp * 2) % MOD;  // 计算偶数环的贡献
                }
            }
            for (int i = 0; i < cycles.size(); i++) {  // 在某个环扣掉两个
                long long size = cycles[i];
                ans += (size / 2) % MOD * (size / 2) % MOD * (size == 2 ? tmp : tmp * 499122177 % MOD) % MOD;
                ans %= MOD;
            }
            std::cout << ans << std::endl;
        }
    }
    return 0;
}

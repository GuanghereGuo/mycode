//
// Created by guanghere on 25-7-17.
//
#include <bits/stdc++.h>
using namespace std;

const int MOD = 998244353;      // 模数
const int MAXN = 500010;        // n 的最大值加一
long long pow2[MAXN];           // pow2[i] = 2^i % MOD

// 预计算 2 的幂次
void precompute() {
    pow2[0] = 1;
    for (int i = 1; i < MAXN; i++) {
        pow2[i] = pow2[i-1] * 2 % MOD;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    precompute();

    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        vector<int> a(n);
        int cnt_minus = 0;       // 统计 -1 的数量
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            if (a[i] == -1) cnt_minus++;
        }

        long long ans = 0;       // 最终答案
        for (int i = 0; i < n; i++) {
            long long contri = 0; // 当前位置的贡献
            if (i == 0) {        // 第一个位置特殊处理
                if (a[0] == 0) {
                    contri = 0;
                } else if (a[0] == 1) {
                    contri = pow2[cnt_minus]; // 条件 i=1 满足
                } else { // a[0] == -1
                    contri = pow2[cnt_minus - 1]; // 选 a[0]=1
                }
            } else {             // i >= 1
                if (a[i] == 0) {
                    contri = 0;
                } else if (a[i] == 1) {
                    if (a[i - 1] == 0) {
                        contri = pow2[cnt_minus]; // 前一位是 0
                    } else if (a[i - 1] == 1) {
                        contri = 0;           // 前一位是 1，不满足
                    } else { // a[i - 1] == -1
                        contri = pow2[cnt_minus - 1]; // a[i-1]=0 的情况
                    }
                } else { // a[i] == -1
                    if (a[i - 1] == 0) {
                        contri = pow2[cnt_minus - 1]; // a[i]=1
                    } else if (a[i - 1] == 1) {
                        contri = 0;           // 不满足
                    } else { // a[i - 1] == -1
                        contri = pow2[cnt_minus - 2]; // a[i]=1, a[i-1]=0
                    }
                }
            }
            ans = (ans + contri) % MOD; // 累加贡献
        }
        cout << ans << '\n';
    }
    return 0;
}

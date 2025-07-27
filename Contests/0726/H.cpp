#include <iostream>
#include <vector>
#include <numeric>
#include <iomanip>
#include <algorithm>
#include <cmath>

// 使用 OI/ACM 风格的常用宏和类型别名
using namespace std;
using ll = long long;
using ld = long double;

const int INF = 1e9;
const int NEG_INF = -1e9;

// Fenwick 树 (或称二元索引树)，用于高效计算前缀最大值
// 这里用于优化 max_segs 的计算
struct FenwickTree {
    vector<int> bit;
    int size;

    FenwickTree(int n) : size(n), bit(n + 1, NEG_INF) {}

    void update(int idx, int val) {
        for (++idx; idx <= size; idx += idx & -idx) {
            bit[idx] = max(bit[idx], val);
        }
    }

    int query(int idx) {
        int max_val = NEG_INF;
        for (++idx; idx > 0; idx -= idx & -idx) {
            max_val = max(max_val, bit[idx]);
        }
        return max_val;
    }
};

// 判定函数：检查是否能将数组划分为 k 段，每段平均值不小于 x
bool check(ld x, int n, int k, const vector<int>& a) {
    vector<ld> b(n);
    for (int i = 0; i < n; ++i) {
        b[i] = static_cast<ld>(a[i]) - x;
    }

    vector<ld> S(n + 1, 0.0);
    for (int i = 0; i < n; ++i) {
        S[i + 1] = S[i] + b[i];
    }

    // 1. 计算 min_segs(x): 划分所需的最少段数
    int min_segs;
    {
        vector<ld> min_S_for_p;
        min_S_for_p.push_back(0.0); // dp[0]=0, S[0]=0
        vector<int> dp(n + 1, 0);
        dp[0] = 0;

        for (int i = 1; i <= n; ++i) {
            // 找到 p = 1 + max{q | min_S_for_p[q] <= S[i]}
            // 等价于在 min_S_for_p 中找到第一个 > S[i] 的位置
            auto it = upper_bound(min_S_for_p.begin(), min_S_for_p.end(), S[i]);
            int p = distance(min_S_for_p.begin(), it);
            dp[i] = p;

            if (p == min_S_for_p.size()) {
                min_S_for_p.push_back(S[i]);
            } else {
                min_S_for_p[p] = min(min_S_for_p[p], S[i]);
            }
        }
        min_segs = dp[n];
    }

    if (min_segs > k) {
        return false;
    }

    // 2. 计算 max_segs(x): 能划分出的最多段数
    int max_segs;
    {
        // 离散化前缀和 S
        vector<ld> sorted_S = S;
        sort(sorted_S.begin(), sorted_S.end());
        sorted_S.erase(unique(sorted_S.begin(), sorted_S.end()), sorted_S.end());

        auto get_coord = [&](ld val) {
            return lower_bound(sorted_S.begin(), sorted_S.end(), val) - sorted_S.begin();
        };

        int m = sorted_S.size();
        FenwickTree ft(m);
        vector<int> dp(n + 1, NEG_INF);

        // base case: dp[0] = 0, S[0] = 0
        dp[0] = 0;
        ft.update(get_coord(S[0]), 0);

        for (int i = 1; i <= n; ++i) {
            int coord = get_coord(S[i]);
            int max_prev_dp = ft.query(coord);

            if (max_prev_dp != NEG_INF) {
                dp[i] = max_prev_dp + 1;
                ft.update(coord, dp[i]);
            }
        }
        max_segs = dp[n];
    }

    return k <= max_segs;
}

int main() {
    // 快速 I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    cin >> n >> k;

    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    ld low = 1.0, high = 1000.0, ans = 1.0;

    // 二分搜索答案，迭代 100 次以保证精度
    for (int iter = 0; iter < 100; ++iter) {
        ld mid = low + (high - low) / 2.0;
        if (check(mid, n, k, a)) {
            ans = mid;
            low = mid;
        } else {
            high = mid;
        }
    }

    cout << fixed << setprecision(12) << ans << endl;

    return 0;
}

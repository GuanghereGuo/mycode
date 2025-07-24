// //
// // Created by guanghere on 25-7-22.
// //
// #include <bits/stdc++.h>
// using namespace std;
//
// int main() {
//     ios::sync_with_stdio(false);
//     cin.tie(nullptr);
//
//     int t;
//     cin >> t;
//     while (t--) {
//         int n;
//         cin >> n;
//
//         vector<pair<int, int>> f(n + 1);
//         vector ans(n + 1, vector(n + 1, 0));
//         for (int i = 1; i <= n; i++) {
//             f[i].second = i;
//             cin >> f[i].first;
//             ans[i][i] = f[i].first - 1;
//         }
//         vector ff = f;
//
//         sort(ff.begin() + 1, ff.end());
//
//         for (int i = n; i >= 1; i--) {
//             int cnt = 1;
//             for (int j = 1; j <= n; j++) {
//                 auto [val, idx] = ff[j];
//                 if (idx < i && cnt < val) {
//                     ans[i][idx] = ans[idx][i] = cnt++;
//                 }
//                 if (cnt >= f[i].first) {
//                     break;
//                 }
//             }
//             for (int j = 1; j <= n; j++) {
//                 auto [val, idx] = ff[j];
//                 if (idx < i && cnt > val && !ans[i][idx] && cnt < f[i].first)
//                 {
//                     ans[i][idx] = ans[idx][i] = cnt++;
//                 }
//                 if (cnt >= f[i].first) {
//                     break;
//                 }
//             }
//         }
//         for (int i = 1; i <= n; i++) {
//             for (int j = 1; j <= n; j++) {
//                 cout << ans[i][j] << " ";
//             }
//             cout << "\n";
//         }
//     }
//     return 0;
// }
// Author: Alencryenfo
// Date: 2025-07-22 13:56:18
#include <iostream>
#include <vector>
using namespace std;

using ll = long long;
using ull = unsigned long long;
int T;

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        vector<int> f(n + 1);
        for (int i = 1; i <= n; ++i) cin >> f[i];
        const int BLANK = 0;
        vector<vector<int>> A(n + 1, vector<int>(n + 1, BLANK));
        vector<vector<char>> used(n + 1, vector<char>(n + 1, 0));
        vector<int> pr(n + 1, 1);
        vector<int> pc(n + 1, 1);
        for (int x = 0; x < n; ++x) {
            vector<char> covered(n + 1, 0);
            for (int i = 1; i <= n; ++i) {
                if (f[i] <= x) continue;
                int &j = pr[i];
                while (j <= n && (used[i][j] || f[j] == x)) ++j;
                if (j > n) {
                    j = 1;
                    while (j <= n && (used[i][j] || f[j] == x)) ++j;
                }
                A[i][j] = x;
                used[i][j] = 1;
                covered[j] = 1;
                ++j;
            }
            for (int j = 1; j <= n; ++j) {
                if (f[j] <= x || covered[j]) continue;
                int &i = pc[j];
                while (i <= n && (used[i][j] || f[i] == x)) ++i;
                if (i > n) {
                    i = 1;
                    while (i <= n && (used[i][j] || f[i] == x)) ++i;
                }
                A[i][j] = x;
                used[i][j] = 1;
                ++i;
            }
        }
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j)
                cout << A[i][j] << (j == n ? '\n' : ' ');
        }
    }
    return 0;
}

/*
{
"C++版本":"C++23",
"优化等级":"-O2",
"时间限制":2000,
"内存限制":512,
"精准匹配":false,
"样例数目":2,
}
1:
<<3
1
1
1
>>1
0
2:
<<7
3
3
1 1 2
5
1 1 3 2 5
4
1 2 1 3
>>12
0 2 0
0 0 0
0 0 1
3 2 0 0 4
0 0 2 0 3
2 4 1 0 2
0 0 1 1 0
2 0 4 3 1
2 0 2 2
0 1 0 1
2 3 0 0
0 0 2 1
*/

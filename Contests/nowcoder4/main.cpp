//Author: Alencryenfo
//Date: 2025-07-24 13:33:53
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

using ll = long long;
using ull = unsigned long long;


signed main() {
    freopen("../output1.txt", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    long long N;
    cin >> N;
    int n = 1   00;
    vector<vector<int> > a(n, vector<int>(n, 0));
    for (int i = 0; i < n / 2; i++) {
        for (int j = i + 1; j < n / 2; j++) {
            a[i][j] = 1;
        }
    }
    for (int i = n / 2; i < n; i++) {
        a[i][i] = 1;
    }
    for (int i = 1; i < n / 2; i++) {
        a[i + n / 2 - 1][i] = 1;
        a[i][i + n / 2 - 1] = 1;
    }
    int i = 0;
    if (N & 1) {
        a[i + 1][0] = 1;
    }
    i++;
    while (N) {
        N >>= 1;
        if (N & 1) {
            a[i + 1][0] = 1;
        }
        i++;
    }
    cout << n - 1 << endl;
    for (int i = 0; i < n - 1; i++) {
        cout << a[1][i] << " ";
    }
    cout << endl;
    for (int i = 0; i < n - 1; i++) {
        cout << a[0][i] << " ";
    }
    cout << endl;
    for (int i = 2; i < n - 1; i++) {
        for (int j = 0; j < n - 1; j++) {
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}

/*
{
"C++版本":"C++23",
"优化等级":"-O2",
"时间限制":2000,
"内存限制":256,
"精准匹配":false,
"样例数目":1,
}
1:
<<1
1
>>2
1
1
2:
<<1
5
>>8
7
0 0 0 1 0 0 1
0 0 1 0 0 1 0
0 1 1 0 0 0 1
0 1 0 1 1 0 0
1 1 0 1 1 1 0
1 1 1 1 0 0 0
1 1 1 0 1 0 0
*/

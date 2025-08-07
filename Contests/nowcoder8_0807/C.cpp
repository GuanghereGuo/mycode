//
// Created by guanghere on 25-8-7.
//
//Author: Alencryenfo
//Date: 2025-08-07 04:15:05
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

using ll = long long;
using ull = unsigned long long;

signed main() {
#ifdef DEBUG
    freopen("test.in", "r", stdin);
    freopen("test.out", "w", stdout);
#endif
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int T;
    cin >> T;
    while(T--){
        int n;
        ll H;
        cin >> n >> H;
        vector<ll> h(n);
        for(int i = 0; i < n; i++){
            cin >> h[i];
        }
        vector<pair<ll,int>> a;
        a.reserve(n);
        for(int i = 0; i < n; i++){
            ll key = h[i] * (H - h[i]);
            a.emplace_back(key, i+1);
        }
        sort(a.begin(), a.end(), [](auto &A, auto &B){
            return A.first < B.first;
        });
        for(int i = 0; i < n; i++){
            cout << a[i].second << (i+1<n ? ' ' : '\n');
        }
    }
    return 0;
}
/*
{
"C++版本":"C++23",
"优化等级":"-O2",
"时间限制":2000,
"内存限制":256,
"自动测试":1,
}
<<5
2
5 10
1 3 5 7 9
5 20
1 3 5 7 9
>>2
1 5 2 4 3
1 2 3 4 5
*/
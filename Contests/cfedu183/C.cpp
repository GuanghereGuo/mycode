#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    for (int test = 0; test < t; ++test) {
        int n;
        cin >> n;
        string s;
        cin >> s;
        vector<int> pre(n + 1, 0);
        for (int i = 1; i <= n; ++i) {
            pre[i] = pre[i - 1] + (s[i - 1] == 'a' ? 1 : -1);
        }
        int tar = pre[n];
        int ans = (tar == 0 ? 0 : INT_MAX);
        map<int, int> mp;
        mp[0] = 0;
        for (int j = 1; j <= n; ++j) {
            int need = pre[j] - tar;
            if (mp.contains(need)) {
                ans = min(ans, j - mp[need]);
            }
            mp[pre[j]] = j;
        }
        cout << (ans == n ? -1 : ans) << '\n';
    }
    return 0;
}
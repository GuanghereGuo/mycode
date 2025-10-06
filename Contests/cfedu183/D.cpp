#include <bits/stdc++.h>
using namespace std;

const int MAXN = 31;
const int MAXS = 500;
bool dp[MAXN][MAXS];

void solve() {
    int n, k;
    cin >> n >> k;
    int total = n * (n - 1) / 2;
    int target = total - k;
    memset(dp, 0, sizeof(dp));
    dp[0][0] = true;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j <= total; ++j) {
            if (!dp[i][j]) continue;
            for (int nl = 1; nl <= n - i; ++nl) {
                int nt = nl * (nl - 1) / 2;
                if (j + nt > total) continue;
                int ni = i + nl;
                dp[ni][j + nt] = true;
            }
        }
    }
    if (!dp[n][target]) {
        cout << 0 << '\n';
        return;
    }
    vector<int> lengths;
    int cur_n = n;
    int cur_s = target;
    while (cur_n > 0) {
        for (int l = 1; l <= cur_n; ++l) {
            int tt = l * (l - 1) / 2;
            if (tt <= cur_s && dp[cur_n - l][cur_s - tt]) {
                lengths.push_back(l);
                cur_n -= l;
                cur_s -= tt;
                break;
            }
        }
    }
    vector<int> p(n);
    int cur_num = n;
    int pos = 0;
    for (int len : lengths) {
        int start = cur_num - len + 1;
        for (int j = 0; j < len; ++j) {
            p[pos++] = start + j;
        }
        cur_num -= len;
    }
    for (int i = 0; i < n; ++i) {
        if (i > 0) cout << " ";
        cout << p[i];
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
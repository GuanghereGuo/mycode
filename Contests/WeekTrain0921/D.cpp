//
// Created by guanghere on 2025/9/21.
//
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    int m = n * k;

    vector<int> a(m + 1), b(m + 1);

    for (int i = 1; i <= m; ++i)
        cin >> a[i];

    vector<vector<int> > pos(n + 1);

    for (int i = 1; i <= n; ++i)
        pos[i].reserve(k);

    for (int j = 1; j <= m; ++j) {
        cin >> b[j];
        pos[b[j]].push_back(j);
    }
    vector<int> d;
    d.reserve(m);
    for (int i = 1; i <= m; ++i) {
        int v = a[i];
        auto &pv = pos[v];
        for (int t = (int) pv.size() - 1; t >= 0; --t) {
            int x = pv[t];
            auto it = lower_bound(d.begin(), d.end(), x);
            if (it == d.end()) d.push_back(x);
            else *it = x;
        }
    }
    cout << (int) d.size() << '\n';
    return 0;
}

//
// Created by guanghere on 25-7-8.
//
#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

signed main() {
    long long T, n, tot;
    cin >> T;
    while (T--) {
        cin >> n;
        vector<long long> ans;
        while ((long long)sqrt(n) * (long long)sqrt(n) != n) {
            ans.push_back(n & -n);
            n += (n & -n);
            tot++;
        }
        cout << ans.size() << endl;
        for (int i = 0; i < ans.size(); i++) {
            if (i) cout << " ";
            cout << ans[i];
        }
        cout << endl;
    }
}
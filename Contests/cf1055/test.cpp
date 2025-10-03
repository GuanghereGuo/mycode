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
        int m = n * n + 1;
        vector<int> r(m);
        iota(r.begin(), r.end(), 1);
        vector<vector<int>> ls;
        bool fd = false;
        vector<int> a;
        for (int q = 0; q < n; ++q) {
            if (r.empty()) break;
            cout << "? " << r.size();
            for (int i : r) cout << " " << i;
            cout << '\n';
            cout.flush();
            int c;
            cin >> c;
            if (c == -1) return 0;
            vector<int> v(c);
            for (int &j : v) cin >> j;
            if (c >= n + 1) {
                a = v;
                fd = true;
                break;
            }
            ls.push_back(v);
            set<int> tr(v.begin(), v.end());
            vector<int> nr;
            for (int i : r) if (!tr.count(i)) nr.push_back(i);
            r = nr;
        }
        cout << "!";
        if (fd) {
            for (int i : a) cout << " " << i;
        } else {
            int cur = r[0];
            vector<int> ch;
            ch.push_back(cur);
            for (int li = ls.size() - 1; li >= 0; --li) {
                int pr = -1;
                for (int j : ls[li]) if (j < cur) pr = max(pr, j);
                cur = pr;
                ch.push_back(cur);
            }
            reverse(ch.begin(), ch.end());
            for (int i : ch) cout << " " << i;
        }
        cout << '\n';
        cout.flush();
    }
    return 0;
}

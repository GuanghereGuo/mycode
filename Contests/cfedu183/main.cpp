#include <bits/stdc++.h>
using namespace std;

struct Fenwick {
    vector<int> tree;
    Fenwick(int nn) : tree(nn + 1, 0) {}
    void upd(int idx, int val) {
        while (idx < tree.size()) {
            tree[idx] += val;
            idx += idx & -idx;
        }
    }
    int que(int idx) {
        int sum = 0;
        while (idx > 0) {
            sum += tree[idx];
            idx -= idx & -idx;
        }
        return sum;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int ac, dr;
    cin >> ac >> dr;
    int n;
    cin >> n;
    vector<int> A(n + 1), D(n + 1);
    for (int i = 1; i <= n; ++i) cin >> A[i];
    for (int i = 1; i <= n; ++i) cin >> D[i];
    const int MAXC = 2000010;
    Fenwick ft(MAXC);
    for (int i = 1; i <= n; ++i) {
        int c = max(0, A[i] - ac) + max(0, D[i] - dr);
        ft.upd(c + 1, 1);
    }
    int m;
    cin >> m;
    for (int qq = 0; qq < m; ++qq) {
        int k, na, nd;
        cin >> k >> na >> nd;
        int oldc = max(0, A[k] - ac) + max(0, D[k] - dr);
        ft.upd(oldc + 1, -1);
        A[k] = na;
        D[k] = nd;
        int newc = max(0, na - ac) + max(0, nd - dr);
        ft.upd(newc + 1, 1);
        int low = 0, high = n;
        while (low < high) {
            int mid = (low + high + 1) / 2;
            int thresh = mid - 1;
            int num = ft.que(thresh + 1);
            if (num >= mid) {
                low = mid;
            } else {
                high = mid - 1;
            }
        }
        int ans = 0;
        if (low >= 1) {
            int thresh = low - 1;
            int num = ft.que(thresh + 1);
            if (num >= low) ans = low;
        }
        cout << ans << '\n';
    }
    return 0;
}
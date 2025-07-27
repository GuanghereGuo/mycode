#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    vector<ll> a(n);
    for (auto &x : a) cin >> x;

    while (q--) {
        ll x, y;
        cin >> x >> y;

        // Find position where a[pos-1] <= x < a[pos]
        int pos = upper_bound(a.begin(), a.end(), x) - a.begin();
        int k = n - pos; // Competitors with score > x
        if (k <= y - 1) {
            cout << 0 << '\n';
            continue;
        }

        // Compute challenge sequence c
        vector<ll> c;
        ll curr_x = x;
        for (int i = pos; i < n; ++i) {
            if (a[i] <= curr_x) continue;
            ll diff = a[i] - curr_x;
            ll c_j = (diff + 1) / 2; // ceil(diff / 2)
            c.push_back(c_j);
            curr_x += c_j;
        }
        int m = c.size();
        if (m == 0) {
            cout << 0 << '\n';
            continue;
        }
        vector<ll> s(m + 1, 0);
        for (int i = 1; i <= m; ++i) {
            s[i] = s[i - 1] + c[i - 1];
        }

        // Binary search for minimal mid
        ll low = 0, high = 1e18;
        while (low < high) {
            ll mid = low + (high - low) / 2;
            ll xm = x + mid;

            // Find largest t where s[t] <= mid
            int t = upper_bound(s.begin(), s.end(), mid) - s.begin() - 1;
            int cnt;
            if (t >= m) {
                cnt = 0; // All competitors fully challenged
            } else {
                // Count j > pos + t with a[j] > xm
                cnt = n - (pos + t) - (upper_bound(a.begin() + pos + t, a.end(), xm) - (a.begin() + pos + t));
                ll r = mid - s[t];
                if (r > 0) {
                    ll final_score = a[pos + t] - r;
                    if (final_score > xm) cnt++;
                }
            }
            if (cnt <= y - 1) {
                high = mid;
            } else {
                low = mid + 1;
            }
        }
        cout << low << '\n';
    }
    return 0;
}

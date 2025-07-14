#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll t, c, b;
    int n, m;
    cin >> t >> c >> n;
    vector<ll> s(n);
    for (auto &x : s) cin >> x;
    cin >> b >> m;
    vector<ll> bi(m);
    for (auto &x : bi) cin >> x;

    vector<ll> ps;
    ps.push_back(0);
    ll cur_t = 0;
    for (int i = 0; ; ++i) {
        cur_t += s[i % n];
        if (cur_t > t) break;
        ps.push_back(cur_t);
    }

    vector<ll> pb;
    pb.push_back(0);
    cur_t = 0;
    ll cur_inc = 0;
    for (int i = 0; ; ++i) {
        ll cost = b + cur_inc;
        if (cur_t + cost > t || cost > 3 * c) break;
        cur_t += cost;
        pb.push_back(cur_t);
        cur_inc += bi[i % m];
    }

    ll ans = 0;
    for (int i = 0; i < ps.size(); ++i) {
        for (int j = 0; j < pb.size(); ++j) {
            ll used_t = ps[i] + pb[j];
            if (used_t > t) break;
            ll left_t = t - used_t;
            ans = max(ans, left_t / c + 2LL * i + 3LL * j);
        }
    }

    cout << ans << endl;

    return 0;
}
//
// Created by guanghere on 25-7-31.
//
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll gcd(ll a, ll b) { return abs(std::gcd(a, b)); }

void solve() {
    int n;
    cin >> n;
    vector<ll> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    bool flag = true;
    for (int i = 1; i < n; ++i) {
        if (a[i] != a[0]) {
            flag = false;
            break;
        }
    }
    if (flag) {
        cout << 0 << "\n";
        return;
    }

    ll ans = abs(a[1] - a[0]);
    for (int i = 2; i < n; ++i) {
        ans = gcd(ans, a[i] - a[i - 1]);
    }

    auto get_divs = [](ll x) {
        vector<ll> divs;
        x = abs(x);
        if (x == 0) return divs;
        for (ll i = 1; i * i <= x; ++i) {
            if (x % i == 0) {
                divs.push_back(i);
                if (i * i != x) {
                    divs.push_back(x / i);
                }
            }
        }
        return divs;
    };

    set<ll> S;
    for (ll d : get_divs(a[0]))
        S.insert(d);
    for (ll d : get_divs(a[n - 1]))
        S.insert(d);

    auto chk = [&](const ll g) {
        int l = -1, r = -1;
        for (int i = 0; i < n; ++i) {
            if (a[i] % g != 0) {
                if (l == -1)
                    l = i;
                r = i;
            }
        }

        if (l == -1) return true;

        ll rem = a[l] % g;
        for (int i = l + 1; i <= r; ++i) {
            if (a[i] % g != rem) return false;
        }
        return true;
    };

    for (ll g : S) {
        if (g > ans && chk(g)) {
            ans = g;
        }
    }

    cout << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}

//
// Created by guanghere on 25-8-5.
//
#include <iostream>
#include <vector>
using namespace std;

using ll = long long;
using ull = unsigned long long;
constexpr ll mod = 998244353;

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n, odd = 0, even = 0;
    cin >> n;
    vector<ll> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i <= n; i++) {
        ll x = a[i];
        if (x & 1) {
            odd++;
        } else {
            even++;
        }
    }
    cout << (odd % mod) * (even % mod) % mod << '\n';

    return 0;
}
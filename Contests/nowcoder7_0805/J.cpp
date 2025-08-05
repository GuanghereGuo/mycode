//
// Created by guanghere on 25-8-5.
//
#include <iostream>
#include <vector>
#include <numeric>
#include <map>
#include <algorithm>

using namespace std;

using ll = long long;
using i128 = __int128_t;

constexpr int mod = 998244353;

ll power(ll base, ll exp) {
    ll res = 1;
    base %= mod;
    while (exp > 0) {
        if (exp % 2 == 1)
            res = (i128)res * base % mod;
        base = (i128)base * base % mod;
        exp /= 2;
    }
    return res;
}

ll mul(ll a, ll b, ll m) {
    return (i128)a * b % m;
}

ll power(ll base, ll exp, ll m) {
    ll res = 1;
    base %= m;
    while (exp > 0) {
        if (exp % 2 == 1) res = mul(res, base, m);
        base = mul(base, base, m);
        exp /= 2;
    }
    return res;
}

bool miller_rabin(ll n) {
    if (n < 2) return false;
    static const vector<ll> witnesses = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (ll p : witnesses) {
        if (n == p) return true;
    }

    ll d = n - 1;
    int s = 0;
    while (d % 2 == 0) {
        d /= 2;
        s++;
    }

    for (ll a : witnesses) {
        ll x = power(a, d, n);
        if (x == 1 || x == n - 1) continue;
        bool flag = true;
        for (int r = 1; r < s; ++r) {
            x = mul(x, x, n);
            if (x == n - 1) {
                flag = false;
                break;
            }
        }
        if (flag) return false;
    }
    return true;
}

// ll pollard_rho(ll n) {
//     if (n % 2 == 0) return 2;
//     if (miller_rabin(n)) return n;
//
//     auto f = [&](ll x, ll c) {
//         return (mul(x, x, n) + c) % n;
//     };
//
//     ll x = 0, y = 0, d = 1;
//     ll c = 1;
//     while (true) {
//         x = 2, y = 2, d = 1;
//         while (d == 1) {
//             x = f(x, c);
//             y = f(f(y, c), c);
//             d = std::gcd(abs(x - y), n);
//         }
//         if (d != n) return d;
//         c++;
//     }
// }
ll pollard_rho(ll x) {
    ll s = 0, t = 0;
    ll c = (ll)rand() % (x - 1) + 1;
    int step = 0, goal = 1;
    ll val = 1;
    for (goal = 1;; goal *= 2, s = t, val = 1) {  // 倍增优化
        for (step = 1; step <= goal; ++step) {
            t = (mul(t, t, x) + c) % x;
            val = mul(val, abs(t - s), x);
            if ((step % 127) == 0) {
                ll d = gcd(val, x);
                if (d > 1) return d;
            }
        }
        ll d = gcd(val, x);
        if (d > 1) return d;
    }
}

void factorize(ll n, map<ll, int>& factors) {
    if (n <= 1) return;
    if (miller_rabin(n)) {
        factors[n]++;
        return;
    }
    ll p = pollard_rho(n);
    factorize(p, factors);
    factorize(n / p, factors);
}


void solve() {
    ll a, b, c, d;
    cin >> a >> b >> c >> d;


    ll g = std::gcd(a, c);
    if (g == 1) {
        cout << 1 << endl;
        return;
    }

    map<ll, int> factors;
    factorize(g, factors);

    ll ans = 1;
    for (auto const& [p, exp_g] : factors) {
        ll va = 0, vc = 0;
        ll temp_a = a, temp_c = c;

        while (temp_a > 0 && temp_a % p == 0) {
            va++;
            temp_a /= p;
        }
        while (temp_c > 0 && temp_c % p == 0) {
            vc++;
            temp_c /= p;
        }

        i128 exp_a = (i128)va * b;
        i128 exp_c = (i128)vc * d;
        i128 final_exp = min(exp_a, exp_c);

        ans = (ans * power(p, final_exp % (mod - 1))) % mod;
    }

    cout << ans << endl;
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

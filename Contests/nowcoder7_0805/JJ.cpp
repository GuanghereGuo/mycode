    #include <iostream>
    #include <numeric>
    #include <algorithm>
    #include <utility>

    using namespace std;

    using ll = long long;
    using i128 = __int128_t;

    const int MOD = 998244353;

    ll power(ll base, ll exp) {
        base %= MOD;
        if (base == 0) return 0;
        if (exp == 0) return 1;
        ll reduced_exp = exp % (MOD - 1);
        ll res = 1;
        while (reduced_exp > 0) {
            if (reduced_exp % 2 == 1) res = (i128)res * base % MOD;
            base = (i128)base * base % MOD;
            reduced_exp /= 2;
        }
        return res;
    }

    ll solve_recursive(ll a, ll b, ll c, ll d) {
        if (a == 1 || c == 1 || b == 0 || d == 0) {
            return 1;
        }

        ll g = std::gcd(a, c);
        if (g == 1) {
            return 1;
        }

        if (b < d) {
            ll term = power(g, b);
            return (term * solve_recursive(a / g, b, g, d - b)) % MOD;
        } else if (d < b) {
            ll term = power(g, d);
            return (term * solve_recursive(g, b - d, c / g, d)) % MOD;
        } else {
            return power(g, b);
        }
    }

    void solve() {
        ll a, b, c, d;
        cin >> a >> b >> c >> d;
        cout << solve_recursive(a, b, c, d) << endl;
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

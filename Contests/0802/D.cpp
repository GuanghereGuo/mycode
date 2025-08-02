//
// Created by guanghere on 25-8-2.
//
#include <bits/stdc++.h>

using ll = long long;
const int MAXN = 100005;
std::vector<int> primes;
bool is_prime[MAXN];

void sieve(int n) {
    std::vector<bool> is_prime(n + 1, true);
    for (int i = 2; i <= n; ++i) {
        if (is_prime[i]) {
            primes.push_back(i);
        }
        for (int j = 0; j < primes.size() && i * primes[j] <= n; ++j) {
            is_prime[i * primes[j]] = false;
            if (i % primes[j] == 0) break;
        }
    }
}

void get_factors(ll n, std::vector<ll>& factors) {
    if (n <= 1) return;
    for (int p : primes) {
        if ((ll)p * p > n) break;
        if (n % p == 0) {
            factors.push_back(p);
            while (n % p == 0) {
                n /= p;
            }
        }
    }
    if (n > 1) {
        factors.push_back(n);
    }
}

void solve() {
    ll x, y;
    std::cin >> x >> y;

    std::vector<ll> forbidden;
    get_factors(x, forbidden);
    get_factors(y, forbidden);

    std::ranges::sort(forbidden);
    forbidden.erase(std::ranges::unique(forbidden).begin(), forbidden.end());

    for (ll k = 1; k <= 500; ++k) {
        ll z = x + k;
        if (z >= y) {
            break;
        }

        bool is_valid = true;
        for (ll p : forbidden) {
            if (z % p == 0) {
                is_valid = false;
                break;
            }
        }

        if (is_valid) {
            std::cout << z << "\n";
            return;
        }
    }

    std::cout << -1 << "\n";
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    sieve(MAXN);

    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }

}

//
// Created by guanghere on 25-7-22.
//
#include <bits/stdc++.h>

std::vector<int> prime;
std::vector is_prime(5e6 + 1, true);

void liner_sieve(const int n = 5e6) {
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i <= n; ++i) {
        if (is_prime[i]) {
            prime.push_back(i);
        }
        for (int j = 0; j < prime.size() && i * prime[j] <= n; ++j) {
            is_prime[i * prime[j]] = false;
            if (i % prime[j] == 0) break;
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    liner_sieve();

    int t;
    std::cin >> t;
    while (t--) {
        std::unordered_map<int, int> mp;
        int n;
        std::cin >> n;
        std::vector<int> a(n + 1);
        for (int i = 1; i <= n; ++i) {
            std::cin >> a[i];
        }
        auto b = a;
        if (n & 1) {
            std::cout << "YES" << '\n';
            continue;
        }
        if (n == 2) {
            std::cout << (a[1] == a[2] ? "YES" : "NO") << '\n';
            continue;
        }
        for (int i = 1; i <= n; i++) {
            if (is_prime[a[i]]) {
                mp[a[i]]++;
                continue;
            }
            for (int j = 0; j < prime.size() && (long long)prime[j] * prime[j] <= a[i]; ++j) {
                while (a[i] % prime[j] == 0) {
                    mp[prime[j]]++;
                    a[i] /= prime[j];
                }
            }
            if (is_prime[a[i]]) {
                mp[a[i]]++;
            }
        }
        bool flag = true;
        for (const auto cnt : mp | std::views::values) {
            if (cnt & 1) {
                std::cout << "NO" << '\n';
                flag = false;
                break;
            }
        }
        if (flag) {
            std::cout << "YES" << '\n';
        }
    }
}
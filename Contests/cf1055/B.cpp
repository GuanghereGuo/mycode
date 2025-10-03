//
// Created by guanghere on 2025/10/3.
//
#include <bits/stdc++.h>

using ll = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    ll t;
    std::cin >> t;
    for (ll i = 0; i < t; i++) {
        ll n, rk, ck, rd, cd;
        std::cin >> n >> rk >> ck >> rd >> cd;
        ll dr = rk - rd;
        ll dc = ck - cd;
        ll adr = abs(dr);
        ll adc = abs(dc);
        ll tr;
        if (dr != 0) {
            ll esr = (dr > 0 ? n - rk : rk);
            ll remc = std::max(0LL, adc - esr);
            ll mm = std::max(adr, remc);
            tr = esr + mm;
        } else {
            ll esr = std::max(rk, n - rk);
            // tr = std::max(esr, adc);
            tr = adc;
        }
        ll tc;
        if (dc != 0) {
            ll esc = (dc > 0 ? n - ck : ck);
            ll remr = std::max(0LL, adr - esc);
            ll mm = std::max(adc, remr);
            tc = esc + mm;
        } else {
            ll esc = std::max(ck, n - ck);
            // tc = std::max(esc, adr);
            tc = adr;
        }
        std::cout << std::max(tr, tc) << '\n';
    }
    return 0;
}


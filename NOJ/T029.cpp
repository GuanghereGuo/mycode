//
// Created by 24087 on 24-10-6.
//
#include <cmath>
#include <iostream>

using ull = unsigned long long;
constexpr ull mod = 1e9 + 7;

ull quick_pow(ull a, ull b) {
    ull ans = 1;
    while(b) {
        if(b & 1) {
            ans = ans * a % mod;
        }
        a = a * a % mod;
        b >>= 1;
    }
    return ans;
}

int main() {
    ull n, odd, even;
    std::cin >> n;
    odd = (n) / 2;
    even = (n) - odd;
    std::cout << quick_pow(4, odd) * quick_pow(5, even) % mod;
}
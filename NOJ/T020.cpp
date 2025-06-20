//
// Created by 24087 on 24-10-5.
//
#include <iostream>

using ull = unsigned long long;

ull quick_pow(ull base, ull exp, const ull mod) {
    ull res = 1;
    while(exp) {
        if(exp & 1) {
            res = res * base % mod;
        }
        base = base * base % mod;
        exp >>= 1;
    }
    return res;
}

int main() {
    ull a, b, m;
    std::cin >> a >> b >> m;
    std::cout << quick_pow(a, b, m) << std::endl;
}
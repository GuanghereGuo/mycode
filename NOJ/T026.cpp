//
// Created by 24087 on 24-10-5.
//
#include <iostream>
#include <vector>

using ull = unsigned long long;

ull my_gcd(ull a, ull b) {
    if(b == 0) {
        return a;
    }
    return my_gcd(b, a % b);
}

bool is_prime(ull n) {
    if(n < 2) {
        return false;
    }
    for(ull i = 2; i * i <= n; i++) {
        if(n % i == 0) {
            return false;
        }
    }
    return true;
}

int main() {
    ull factorial = 1;
    ull k;
    std::cin >> k;
    if(is_prime(k)) {
        std::cout << k;
        return 0;
    }
    int i = 2;
    for(i = 2; k > 1; i++) {
        k /= my_gcd(k, i);
    }
    std::cout << i - 1;
}

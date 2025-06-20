//
// Created by 24087 on 24-10-6.
//
#include <iostream>

#define int long long

int my_gcd(int a, int b) {
    if (b == 0) return a;
    return my_gcd(b, a % b);
}

signed main() {
    int n, x;
    std::cin >> n >> x;
    std::cout << 3 * (n - my_gcd(n, x));
}
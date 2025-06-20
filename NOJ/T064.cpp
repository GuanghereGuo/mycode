//
// Created by 24087 on 24-10-15.
//
#include <iostream>

int main() {
    long long n;
    std::cin >> n;
    long long cnt = 1;
    //Catalan number
    for (long long i = n + 2; i <= 2 * n; ++i)
        cnt *= i;
    for (long long i = 1; i <= n; ++i)
        cnt /= i;
    std::cout << cnt;
}
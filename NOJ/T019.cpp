//
// Created by 24087 on 24-10-5.
//
#include <bits/stl_algo.h>
#include <cmath>
#include <iostream>

int mygcd(int a, int b) {
    if(a < b) {
        std::swap(a, b);
    }
    // gcd(a, b) = gcd(b, a % b)
    while(b != 0) {
        int temp = a % b;
        a = b;
        b = temp;
    }
    return a;
}

int main() {
    double ori, x;
    std::cin >> ori;
    x = ori;
    int lower = 1;
    while(floor(x) != x) {
        x *= 10;
        lower *= 10;
    }
    int upper = static_cast<int>(x);
    int gcd = mygcd(upper, lower);
    std::cout << upper / gcd << '/' << lower / gcd << std::endl;
}
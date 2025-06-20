//
// Created by 24087 on 24-10-5.
//
#include <iostream>

int main() {
    int a, b, ans;
    std::cin >> a >> b;
    ans =  a * b;
    while(a > 0) {
        std::cout << a << ' ' << b << '\n';
        a /= 2;
        b *= 2;
    }
    std::cout << ans;
}
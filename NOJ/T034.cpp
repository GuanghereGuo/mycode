//
// Created by 24087 on 24-10-7.
//
#include <iostream>

int pb(int n) {
    // 递推方法
    int p0 = 0, p1 = 1, pn = 0;
    for (int i = 0; i <= n; i++) {
        if (i == 0)
            pn = p0;
        else if (i == 1)
            pn = p1;
        else {
            pn = 2 * p1 + p0;
            p0 = p1;
            p1 = pn;
        }
    }
    return pn;
}

int main() {
    int n;
    std::cin >> n;
    std::cout << pb(n);
}
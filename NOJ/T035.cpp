//
// Created by 24087 on 24-10-7.
//
#include <iostream>

int HarshadNumber(int n){
    int t = n, s = 0;
    while (t) {
        s += t%10;
        t /= 10;
    }
    if ((s == 0) || (n%s != 0)) return 0;
    if (s == 1) return 1;
    return n/s;
}

int main() {
    int n;
    std::cin >> n;
    int cnt = 0;
    n = HarshadNumber(n);
    while(n != 0) {
        cnt++;
        if(n == 1)
            break;
        n = HarshadNumber(n);
    }
    std::cout << cnt;
}
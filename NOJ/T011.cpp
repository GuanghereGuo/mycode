//
// Created by 24087 on 24-9-25.
//
#include <iostream>

int get_sum(int x) {
    int sum = 0;
    while(x != 0) {
        sum += x % 10;
        x /= 10;
    }
    return sum;
}

int main() {
    int  n, cnt = 0;
    std::cin >> n;
    while(n != 0) {
        cnt++;
        n -= get_sum(n);
    }
    std::cout << cnt;
}
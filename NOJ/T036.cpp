//
// Created by 24087 on 24-10-7.
//
#include <array>
#include <iostream>

std::array<int, 8> arr = {0};

int init(int n) {
    int cnt = 0;
    while (n) {
        arr[cnt++] = n % 10;
        n /= 10;
    }
    return cnt;
}

void is_keith(int n, int len) {
    int i = len - 1;
    while (arr[i] < n) {
        int sum = 0;
        for (int j = 0; j < len; ++j) {
            sum += arr[(i - j + len) % len];
        }
        arr[i] = sum;
        i = (i - 1 + len) % len;
    }
    if (arr[i] == n)
        std::cout << "Yes";
    else
        std::cout << "No";
}

int main() {
    int n;
    std::cin >> n;
    is_keith(n, init(n));
}
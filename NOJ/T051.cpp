//
// Created by 24087 on 24-10-9.
//
#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>

int main() {
    // add
    std::string a, b;
    std::cin >> a >> b;
    if (a.size() < b.size())
        std::swap(a, b);
    for (auto &c : a) {
        if (isdigit(c)) {
            c -= '0';
        } else {
            c = c - 'A' + 10;
        }
    }
    for (auto &c : b) {
        if (isdigit(c)) {
            c -= '0';
        } else {
            c = c - 'A' + 10;
        }
    }

    for (int i = 0; i < b.size(); i++) {
        a[a.size() - 1 - i] += b[b.size() - 1 - i];
    }

    for (int i = 0; i < a.size() - 1; i++) {
        std::cerr << a.size() << std::endl;
        if (a[a.size() - 1 - i] >= 36) {
            a[a.size() - 1 - i] -= 36;
            a[a.size() - i - 2]++;
        }
    }
    if(a[0] >= 36) {
        a[0] -= 36;
        a = "1" + a;
        a[0] -= '0';
    }
    for (auto &c : a) {
        if (c < 10) {
            c += '0';
        } else {
            c = c - 10 + 'A';
        }
    }
    std::cout << a;
}
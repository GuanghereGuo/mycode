//
// Created by 24087 on 24-10-9.
//
#include <algorithm>
#include <iostream>
#include <string>

int main() {
    std::string str;
    std::cin >> str;
    std::sort(str.begin(), str.begin() + static_cast<int>(str.size()) / 2, std::greater<>());
    std::reverse(str.begin() + (static_cast<int>(str.size()) + 1) / 2, str.end());
    std::cout << str;
}
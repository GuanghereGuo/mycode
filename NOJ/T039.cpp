//
// Created by 24087 on 24-10-7.
//
#include <iostream>
#include <string>

void binary(int a, std::string& result) {
    bool flag = false;
    for (int i = 15; i >= 0; --i) {
        if ((a >> i) & 1) {
            if (flag) result += "+";
            if (i >= 2) {
                result += "2(";
                binary(i, result);
                result += ")";
            }
            if (i == 1) result += "2";
            if (i == 0) result += "2(0)";
            flag = true;
        }
    }
}

int main() {
    int a;
    std::cin >> a;
    std::string result;
    binary(a, result);
    std::cout << result;
}
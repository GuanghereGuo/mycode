//
// Created by 24087 on 24-10-10.
//
#include <iostream>
#include <string>

int main() {
    std::string str, suffix;
    std::getline(std::cin, str);
    std::getline(std::cin, suffix);
    if(str.rfind(suffix) == str.size() - suffix.size()) {
        std::cout << "Yes";
    } else {
        std::cout << "No";
    }
}
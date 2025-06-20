//
// Created by 24087 on 24-10-10.
//
#include <iostream>
#include <string>

int main() {
    std::string str, olds, news;
    std::getline(std::cin, str);
    std::getline(std::cin, olds);
    std::getline(std::cin, news);
    while(str.find(olds) != std::string::npos) {
        str.replace(str.find(olds), olds.size(), news);
    }
    std::cout << str;
}
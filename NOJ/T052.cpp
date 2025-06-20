//
// Created by 24087 on 24-10-9.
//
#include <iostream>
#include <string>

int main() {
    std::string str, text;
    std::getline(std::cin, str);
    std::getline(std::cin, text);
    std::string prefix = str, suffix = str;

    while(prefix.find(text) == 0) {
        prefix.erase(0, text.size());
    }

    while(suffix.rfind(text) == suffix.size() - text.size())
        suffix.erase(suffix.size() - text.size(), text.size());
    std::cout << prefix << std::endl << suffix;
}
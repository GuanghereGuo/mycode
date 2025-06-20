//
// Created by 24087 on 24-10-10.
//
#include <iostream>
#include <regex>
#include <string>
#include <vector>

auto split(const std::string& str, const std::string& sep) {
    if(sep == ".") {
        std::string tmp = "\\.";
        return split(str, tmp);
    }
    std::regex reg(sep);
    std::vector<std::string> ret(
        std::sregex_token_iterator(str.begin(), str.end(), reg, -1),
        std::sregex_token_iterator());
    return ret;
}

int main() {
    std::string str;
    std::string sep;
    std::getline(std::cin, str);
    std::getline(std::cin, sep);
    auto ret = split(str, sep);
    for (const auto& i : ret) {
        std::cout << i << std::endl;
    }
}
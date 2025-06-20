#include <iostream>
#include <string>

void strLeftStrip(std::string &str, const std::string &chars) {
    str.erase(0, str.find_first_not_of(chars));
}

void strRightStrip(std::string &str, const std::string &chars) {
    str.erase(str.find_last_not_of(chars) + 1);
}

int main() {
    std::string str1, chars;
    std::getline(std::cin, str1);
    std::getline(std::cin, chars);
    std::string str2 = str1;

    strLeftStrip(str1, chars);
    std::cout << str1 << std::endl;
    strRightStrip(str2, chars);
    std::cout << str2 << std::endl;
    strRightStrip(str1, chars);
    std::cout << str1 << std::endl;
}
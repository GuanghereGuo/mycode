//
// Created by 24087 on 24-10-15.
//
#include <iostream>
#include <string>
#include <cctype>

int main() {
    std::string str;
    std::getline(std::cin, str);
    for(char &ch : str) {
        if(isupper(ch)) {
            ch = tolower(ch);
        } else if(islower(ch)) {
            ch = toupper(ch);
        }
    }
    std::cout << str;
}

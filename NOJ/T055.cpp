//
// Created by 24087 on 24-10-10.
//
#include <climits>
#include <iostream>
#include <string>

int string_to_long(const std::string& str) {
    int sgn = 1;
    long long tmp = 0;
    std::size_t i = 0;

    for(; str[i] == ' '; i++) {
    }

    if (str[i] == '+') {
        ++i;
    } else if (str[i] == '-') {
        sgn = -1;
        ++i;
    }

    while (i < str.size()) {
        if (str[i] == ' ') {
            continue;
        }
        if ('0' <= str[i] && str[i] <= '9') {
            tmp = (str[i] - '0') + tmp * 10;
            if ((tmp * sgn) >= INT_MAX) return INT_MAX;
            if ((tmp * sgn) <= INT_MIN) return INT_MIN;
        } else {
            break;
        }
        ++i;
    }
    return tmp * sgn;
}

int main() {
    std::string str;
    std::getline(std::cin, str);
    std::cout << string_to_long(str) << std::endl;
}

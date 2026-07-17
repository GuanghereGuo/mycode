//
// Created by guanghere on 2026/7/17.
//
#include <iostream>
#include <string>

bool is_vowel(char ch) {
    return ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u';
}

bool is_meme_language(const std::string &s) {
    if (s.size() != 8) {
        return false;
    }

    for (std::size_t i = 0; i < s.size(); ++i) {
        if (i % 2 == 0) {
            // 第 1、3、5、7 个字符必须是辅音
            if (is_vowel(s[i])) {
                return false;
            }
        } else {
            // 第 2、4、6、8 个字符必须是元音
            if (!is_vowel(s[i])) {
                return false;
            }
        }
    }

    return true;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    while (n--) {
        std::string s;
        std::cin >> s;

        if (is_meme_language(s)) {
            std::cout << "Suspected Virus\n";
        } else {
            std::cout << "Well-Being\n";
        }
    }

    return 0;
}
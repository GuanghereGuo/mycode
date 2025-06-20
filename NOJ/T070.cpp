//
// Created by 24087 on 24-10-16.
//
#include <iostream>
#include <string>
#include <unordered_map>

void change(char &ch, int x) {
    ch += x;
    if(ch > 'z') {
        ch = ch - 'z' + 'a' - 1;
    } else if(ch < 'a') {
        ch = 'z' - 'a' + ch + 1;
    }
}

int main() {
    std::string s;
    int x;
    std::cin >> s >> x;
    std::unordered_map<char, int> m;
    for (char c : s) {
        m[c]++;
    }
    for (auto &ch : s) {
        if (m[ch] & 1) {
            change(ch, -x);
        } else {
            change(ch, x);
        }
    }
    std::cout << s;
}
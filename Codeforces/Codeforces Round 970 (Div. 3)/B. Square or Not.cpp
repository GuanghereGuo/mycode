//
// Created by 24087 on 9/3/2024.
//
#include <iostream>
#include <string>
#include <bitset>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int t;
    std::cin >> t;
    while(t--) {
        int len;
        std::string str;
        std::cin >> len >> str;

        if(len <= 4) {
            if((len == 1 && str[0] == '1') || (len == 4 && str.find('0') == std::string::npos)) {
                std::cout << "Yes\n";
            } else {
                std::cout << "No\n";
            }
        } else  {
            size_t col = str.find('0');
            if (col == std::string::npos) {
                std::cout << "No\n";
                continue;
            }
            col--;

            if (col * col == len) {
                std::cout << "Yes\n";
            } else {
                std::cout << "No\n";
            }
        }

    }
}

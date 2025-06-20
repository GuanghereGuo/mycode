//
// Created by 24087 on 24-9-28.
//
#include <iostream>
#include <vector>
#include <string>

int main() {
    std::string str;
    std::cin >> str;
    std::vector<int> dp(str.size() + 1);

    if(str.size() == 1) {
        std::cout << (str[0] == 'm' || str[0] == 'w' ? 0 : 1);
        return 0;
    }

    if(str[1] == 'm' || str[1] == 'w') {
        std::cout << 0;
        return 0;
    }

    dp[0] = 1;
    dp[1] = 1;
    if(str[0] == 'n' || str[0] == 'u') {
        if(str[1] == str[0]) {
            dp[1] = 2;
        }
    }

    for(int i = 2; i < str.size(); i++) {
        if(str[i] == 'm' || str[i] == 'w') {
            std::cout << 0;
            return 0;
        }
        if(str[i] == 'n' || str[i] == 'u') {
            if(str[i - 1] == str[i]) {
                dp[i] += dp[i - 2];
            }
        }
        dp[i] += dp[i - 1];
    }
    std::cout << dp[str.size() - 1];
}
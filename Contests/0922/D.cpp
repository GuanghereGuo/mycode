//
// Created by 24087 on 9/22/2024.
//
#include <iostream>
#include <string>
#include <climits>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int t;
    std::cin >> t;

    while(t--) {
        int n;
        std::cin >> n;
        std::string str;
        std::cin >> str;
        int count_1 = (str[0] == '1') ? 1 : 0;
        bool flag = false;

        if(n == 1) {
            std::cout << 0 << '\n';
            continue;
        }

        for(int i = 1; i < n; i++) {
            if(str[i] == '1')
                count_1++;
            else if(str[i - 1] == '0') {
                flag = true;
            }
        }

        if(str[0] == '0' || str[n - 1] == '0')
            flag = true;

        if(flag) {
            std::cout << count_1 << '\n';
        } else {
            int len = INT_MAX, idx = 0;//idx -> the first 1

            for(int i = 0; i < n; i++) {
                if(str[i] == '0') { //the first 0
                    len = std::min(len, i - idx);
                    idx = i;
                    while(str[idx] == '0')
                        idx++;
                    i = idx;
                }
            }
            len = std::min(len, n - idx);
            std::cout << count_1 + len << '\n';
        }
    }
}

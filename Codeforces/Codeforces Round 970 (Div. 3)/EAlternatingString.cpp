//
// Created by 24087 on 9/7/2024.
//
#include <iostream>
#include <array>
#include <string>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int t;
    std::cin >> t;

    while(t--) {
        std::array<int, 26> lft[2] = {{0}}, rht[2] = {{0}}; //
        int n = 0;
        std::string str;

        std::cin >> n;
        std::cin >> str;

        if(n == 1 || n == 3) {
            std::cout << 1 << '\n';
            continue;
        }
        if(n == 2) {
            std::cout << 0 << '\n';
            continue;
        }

        if(n % 2 == 0) {
            for(int i = 0; i < n; i++) {
                lft[i % 2][str[i] - 'a']++;
            }
            int max[2] = {0, 0};
            for(int i = 0; i < 26; i++) {
                max[0] = std::max(max[0], lft[0][i]);
            }
            for(int i = 0; i < 26; i++) {
                max[1] = std::max(max[1], lft[1][i]);
            }
            std::cout << n - max[0] - max[1] << '\n';
        } else {
            for(int i = 0; i < n; i++) {
                lft[i % 2][str[i] - 'a']++;
            }
            lft[(n - 1) % 2][str[n - 1] - 'a']--;
            int max[2] = {0, 0};
            for(int i = 0; i < 26; i++) {
                max[0] = std::max(max[0], lft[0][i]);
            }
            for(int i = 0; i < 26; i++) {
                max[1] = std::max(max[1], lft[1][i]);
            }
            int min_ans = n - max[0] - max[1];
            for(int i = n - 2; i >= 0; i--) {//delete i
                max[0] = max[1] = 0;
                lft[i % 2][str[i] - 'a']--;
                rht[(i + 1) % 2][str[i + 1] -'a']++;
                for(int j = 0; j < 26; j++) {
                    max[0] = std::max(max[0], lft[0][j] + rht[1][j]);
                }
                for(int j = 0; j < 26; j++) {
                    max[1] = std::max(max[1], lft[1][j] + rht[0][j]);
                }
                min_ans = std::min(min_ans, n - max[0] - max[1]);
            }
            std::cout << min_ans << '\n';
        }
    }
}

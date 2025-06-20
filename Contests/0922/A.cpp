//
// Created by 24087 on 9/22/2024.
//
#include <iostream>
#include <string>
#include <unordered_map>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int t;
    std::cin >> t;

    while(t--) {
        std::string str;
        std::unordered_map<char, int> mp;
        std::cin >> str;
        if(str.size() == 1) {
            std::cout << "YES\n" << str << '\n';
            continue;
        }
        for(auto i : str) {
            mp[i]++;
        }
        if(mp.size() == 1) {
            std::cout << "NO\n";
            continue;
        }
        if(mp.size() == 2) {
            bool flag = false;
            auto it = mp.cbegin();
            while(it != mp.cend()) {
                if(it -> second == 1) {
                    flag = true;
                    break;
                }
                ++it;
            }
            if(flag == false) {
                std::cout << "NO\n";
            } else {
                std::string ans = "YES\n";
                ans.push_back(it -> first);
                ++it;
                if(it == mp.cend()) {
                    it = mp.cbegin();
                }
                ans += std::string(it -> second, it -> first);
                std::cout << ans << '\n';
            }
            continue;
        }

        auto it = mp.begin();
        std::string ans = "YES\n";
        while(it != mp.end()) {
            ans.push_back(it -> first);
            it -> second--;

            if(it -> second == 0) {
                it = mp.erase(it);
            }
            else
                ++it;
            if(it == mp.end()) {
                it = mp.begin();
            }
        }
        std::cout << ans << '\n';
    }
}

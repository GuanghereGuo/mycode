//
// Created by 24087 on 24-9-26.
//
#include <iostream>
#include <map>
#include <cctype>

int get_num(int x, const std::string &str) {
    int res = 0;
    for (; isdigit(str[x]) && x < str.size(); x++)
        res = res * 10 + str[x] - '0';
    return (res == 0 ? 1 : res);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    std::string str;
    std::cin >> str;
    std::map<std::string, int> mp;

    for (int i = 0; i < static_cast<int>(str.size()); i++) {
        if (!isupper(str[i]))
            continue;
        std::string ele;
        ele.push_back(str[i]);

        if(i == str.size() - 1) {
            mp[ele]++;
            break;
        }
        if (islower(str[i + 1])) {
            ele += str[i + 1];
            mp[ele] += (i + 2 < str.size() ? get_num(i + 2, str) : 1);
        } else
            mp[ele] += get_num(i + 1, str);
    }

    for (auto &[ele, num] : mp)
        std::cout << ele << " " << num << '\n';

}
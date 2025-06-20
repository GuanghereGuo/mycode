//
// Created by 24087 on 24-10-31.
//
#include <format>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);

    int T;
    std::cin >> T;
    while (T--) {
        std::string str;
        std::cin >> str;
        if (str[0] != '>' || str.substr(str.size() - 3, 3) != ">>>" ||
            str.find('-') == std::string::npos) {
            std::cout << "No\n";
            continue;
        }

        std::cout << std::format(
            "Yes {}\n1 {}\n",
            std::accumulate(str.begin(), str.end(), 0,
                            [](int sum, char c) { return sum + (c == '>'); }) -
                3,
            str.size());

        int j = static_cast<int>(str.size()) - 4;
        for (; j >= 0 && str[j] == '>'; --j) {
            std::cout << std::format("1 {}\n", j + 3);
        }
        for (int i = 1; i < j; ++i) {
            if (str[i] == '>') {
                std::cout << std::format("{} {}\n", i + 1, j + 4 - i);
            }
        }
    }
}

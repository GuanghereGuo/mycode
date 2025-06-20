//
// Created by guanghere on 25-3-30.
//
#include <iostream>
#include <unordered_map>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n;
    std::cin >> n;

    std::pmr::unordered_map<std::string, int> map;

    int max_n = 0;
    std::string max_s;
    for (int i = 0; i < n; ++i) {
        std::string s;
        std::cin >> s;
        map[s]++;
        if (map[s] > max_n) {
            max_n = map[s];
            max_s = s;
        }
    }
    std::cout << max_s << "\n";
}
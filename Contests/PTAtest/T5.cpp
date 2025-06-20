//
// Created by guanghere on 25-4-12.
//
#include <iostream>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, m;
    std::cin >> n >> m;
    std::cin.ignore();
    for (int i = 1; i <= n; i++) {
        std::string s;
        std::getline(std::cin, s);
        if (s.find("qiandao") != std::string::npos ||
            s.find("easy") != std::string::npos) {
            continue;
        }
        if (m-- == 0) {
            std::cout << s;
            return 0;
        }
    }
    std::cout << "Wo AK le";
}
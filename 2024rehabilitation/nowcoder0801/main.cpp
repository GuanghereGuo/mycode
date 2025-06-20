#include <iostream>
#include <string>

bool check(const std::string &str) {
    bool last_non_promotional = false;
    int count_of_all = 0, count_of_3 = 0;
    for (const char ch : str) {
        switch (ch) {
            case '3':
                count_of_3++;
                count_of_all++;
                if (count_of_3 >= 10 || count_of_all >= 90) {
                    return false;
                }
                break;
            case '4':
                count_of_3 = 0;
                count_of_all++;
                if (count_of_all >= 90) {
                    return false;
                }
                break;
            case '5':
                if (last_non_promotional) {
                    return false;
                }
                count_of_3 = 0;
                count_of_all = 0;
                last_non_promotional = true;
                break;
            case 'U':
                count_of_3 = 0;
                count_of_all = 0;
                last_non_promotional = false;
                break;
            default:
                std::cerr << "ERR!!!\n";
        }
    }
    return true;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int T;
    std::cin >> T;
    while (T--) {
        std::string str;
        std::cin >> str;
        std::cout << (check(str) ? "valid\n": "invalid\n");
    }
}

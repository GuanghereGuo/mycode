#include <iostream>
#include <string>

int t, n, len;
std::string str;

void strSlice(int begin, int end, int step) {
    std::string slice;
    if (begin < 0) begin += len;
    if (end < 0) end += len;
    if (end >= begin && step > 0) {
        for (int i = begin; i < end; i += step) {
            slice += str[i];
        }
    } else if (end < begin && step < 0) {
        for (int i = begin; i > end; i += step) {
            slice += str[i];
        }
    }
    std::cout << slice << std::endl;
}

int main() {
    std::getline(std::cin, str);
    std::cin >> t;
    for (int i = 0; i < t; ++i) {
        std::cin >> n;
        len = str.size();
        int begin, end, step;
        switch (n) {
            case 3: {
                std::cin >> begin >> end >> step;
                break;
            }
            case 2: {
                std::cin >> begin >> end;
                step = 1;
                break;
            }
            case 1: {
                std::cin >> begin;
                end = len;
                step = 1;
                break;
            }
            default:
                std::cerr << "Invalid input" << std::endl;
                break;
        }
        strSlice(begin, end, step);
    }
}
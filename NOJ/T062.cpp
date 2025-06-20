#include <iostream>
#include <array>

constexpr std::array digit = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6};

int get_unit(int num) {
    int cnt = 0;
    do {
        cnt += digit[num % 10];
        num /= 10;
    } while (num);
    return cnt;
}

int main() {
    int n;
    std::cin >> n;
    n -= 4;
    if (n <= 0) std::cout << "0";
    else {
        int cnt = 0;
        for (int i = 0; i <= 1111; ++i) {
            for (int j = 0; j <= 1111; ++j) {
                if (get_unit(i) + get_unit(j) + get_unit(i + j) == n) ++cnt;
            }
        }
        std::cout << cnt;
    }
}
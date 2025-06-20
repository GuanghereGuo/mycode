#include <iostream>

int main() {

    int cnt = 0, n;
    std::cin >> n;

    for (int a = 0; a <= 9; a++) {
        for (int b = 0; b <= 9; b++) {
            for (int c = 0; c <= 9; c++) {
                for (int d = 0; d <= 9; d++) {
                    int m = a + b + c + d;
                    if (m == n) {
                        ++cnt;
                    }
                }
            }
        }
    }

    std::cout << cnt;

    return 0;
}
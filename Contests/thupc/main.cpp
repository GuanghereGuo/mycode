#include <iostream>
#include <cstdlib>

int main() {
    //freopen("../test.txt", "w", stdout);
    srand(time(0));
    int n = 100;
    std::cout << "1\n";
    for (int i = 1; i <= n; i++) {
        int opt = rand() % 3;
        if (opt == 0) {
            std::cout << "W";
        } else if (opt == 1) {
            std::cout << "M";
        } else {
            std::cout << "X";
        }
    }
}

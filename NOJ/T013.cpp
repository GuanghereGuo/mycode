#include <iostream>

int main() {

    int n;
    std::cin >> n;

    const int left = (n / 100) % 10;
    const int middle = (n / 10) % 10;
    const int right = n % 10;

    if ((middle == 0 || middle == 1 || middle == 8) &&
        ((left == 6 && right == 9) || (left == 9 && right == 6) ||
         ((left == 0 || left == 1 || left == 8) && (right == 0 || right == 1 || right == 8)))) {
        std::cout << "Yes\n";
    } else {
        std::cout << "No\n";
    }

    return 0;
}
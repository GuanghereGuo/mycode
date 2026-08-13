#include <iostream>
#include <string>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int a, b, c;
    std::cin >> a >> b >> c;

    std::string x1, y1, x2, y2;

    if (a <= b) {
        x1 = "2" + std::string(a, '0');
        x2 = "2" + std::string(a - 1, '0') + "9";
        y1 = "4" + std::string(b, '9');
        y2 = y1;
    } else {
        x1 = "1" + std::string(a, '9');
        x2 = x1;
        y1 = "5" + std::string(b, '0');
        y2 = "5" + std::string(b - 1, '0') + "9";
    }

    std::cout << x1 << ' ' << y1 << ' ' << x2 << ' ' << y2 << '\n';
}
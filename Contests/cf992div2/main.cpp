#include <iostream>
#include <cmath>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int t;
    std::cin >> t;
    while (t--) {
        int n;
        std::cin >> n;
        std::cout << static_cast<int>(std::ceil(std::log2((2 + n) / 3.0))) + 1 << '\n';
    }
    return 0;
}

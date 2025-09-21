#include <iostream>
using ll = long long;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    ll n, p;
    std::cin >> n >> p;

    if (n % p == 0) {
        std::cout << 0 << '\n';
        return 0;
    }

    ll k = n / p;
    if (k % 2 != 0) {
        std::cout << n % p << '\n';
    } else {
        std::cout << (n % p) + p << '\n';
    }

    return 0;
}

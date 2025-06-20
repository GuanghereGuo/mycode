#include <cmath>
#include <iostream>
#include <vector>
#include <bit>

using namespace std;

constexpr long long mod = 998244353;

#define int long long

struct countWays {
    using ull = long long;
    std::pmr::vector<std::pmr::vector<ull>> vec;

    explicit countWays(const int n) { vec.resize(n + 2, std::pmr::vector<ull>(static_cast<int>(log2(n)) + 2, 0)); }
    ull calculate(int n, int maxPowerOfTwo) {
        if (n < 0 || maxPowerOfTwo < 0)
            return 0;

        if (n == 0)
            return 1;

        if (vec[n][maxPowerOfTwo]) {
            return vec[n][maxPowerOfTwo];
        }
        // 不选择当前的 2 的幂次 (maxPowerOfTwo)，或者选择它并从 n 减去 2^maxPowerOfTwo
        return vec[n][maxPowerOfTwo] =
                       (calculate (n, maxPowerOfTwo - 1) % mod +
                        calculate(n - (1 << maxPowerOfTwo), maxPowerOfTwo) % mod) %
                       mod;
    }
};


signed main() {
    int n; // 输入的正整数
    std::cin >> n;
    countWays calculator(n);
    // 输出拆分方法数
    cout << calculator.calculate(n, static_cast<int>(log2(n))) << endl;

    int f[114514] = {0};
    f[0] = 1;

    for (int i = 1; i <= n; i++) {
        int t = std::bit_width(static_cast<unsigned>(i - 1));
        for (int j = 0; j < t; j++)
            f[i] = (f[i] + f[i - (1 << j) >> j]) % mod;
    }

    while (true) {
        std::cin >> n;
        cout << calculator.calculate(n, static_cast<int>(log2(n))) << endl;
        std::cerr << f[n] << endl;
    }

    unsigned test = 7;
    std::cout << std::bit_width(test);
}

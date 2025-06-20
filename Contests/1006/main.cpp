#include <iostream>
#include <bitset>
#include <array>
#include <unordered_map>

using ull = unsigned long long;
constexpr ull mod = 1e9 + 7;
constexpr int MAX_N = 3005;

std::array<ull, MAX_N> factorial;
int c;
std::unordered_map<std::bitset<MAX_N>, ull> memo;

void init_factorial(const int n) {
    factorial[0] = 1;
    for(int i = 1; i <= n; i++) {
        factorial[i] = factorial[i - 1] * i % mod;
    }
}

ull quick_pow(ull base, ull exp) {
    ull res = 1;
    while(exp) {
        if(exp & 1) {
            res = res * base % mod;
        }
        base = base * base % mod;
        exp >>= 1;
    }
    return res;
}

ull inv(const ull n) {
    return quick_pow(n, mod - 2);
}

ull C(const ull n, const ull m) {
    return factorial[n] * inv(factorial[m]) % mod * inv(factorial[n - m]) % mod;
}

int get_high_bit(const std::bitset<MAX_N> &bs) {
    int i;
    for (i = MAX_N - 1; i >= 0; i -= 64) {
        if((bs >> i).any()) {
            break;
        }
    }
    for(i += 64; i >= 0; i--) {
        if(bs[i]) {
            return i;
        }
    }
    return -1;
}

ull calculate(const std::bitset<MAX_N> &bs, int depth = 0) {
    if (memo.find(bs) != memo.end()) {
        return memo[bs];
    }

    const int highest_bit = get_high_bit(bs);
    if(highest_bit == -1) {
        return 0;
    }

    ull ans  = 0;
    for(int i = 0; i <= highest_bit; i++) {
        ans += C(highest_bit, i) * quick_pow(c, i + depth) % mod;
        ans %= mod;
    }

    std::bitset<MAX_N> new_bs = bs;
    new_bs[highest_bit] = 0;
    ans += calculate(new_bs, depth + 1);
    ans %= mod;

    memo[bs] = ans;
    return ans;
}

int main() {
    std::bitset<MAX_N> bs;
    std::cin >> bs;
    std::cin >> c;

    init_factorial(get_high_bit(bs) + 5);

    std::cout << (calculate(bs) + quick_pow(c, bs.count())) % mod << std::endl;
}
//
// Created by 24087 on 24-10-6.
//
#include <iostream>
#include <bitset>
#include <vector>
#include <cassert>

using ull = unsigned long long;
constexpr ull mod = 1e9 + 7;

std::vector<ull> factorial;
int c;

void init_factorial(const int n) {
    factorial.push_back(1);
    for(int i = 1; i <= n; i++) {
        factorial.push_back(factorial[i - 1] * i % mod);
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

int get_high_bit(const std::string &bs) {
    return bs.find_first_of('1');
}

int get_lowest_bit(const std::string &bs) {
    return bs.find_last_of('1');
}

ull calculate(const std::string &bs, int depth = 0) {
    const auto highest_pos = get_high_bit(bs);
    if(highest_pos == -1) {
        return 0;
    }
    ull ans  = 0;
    int highest_bit = bs.size() - highest_pos - 1;
    for(int i = 0; i <= highest_bit; i++) {
        ans += C(highest_bit, i) * quick_pow(c, i + depth) % mod;
        ans %= mod;
    }
    std::string new_bs = bs;
    new_bs[highest_pos] = '0';
    ans += calculate(new_bs, depth + 1);
    ans %= mod;
    return ( ans ) % mod;
}

int count(std::string &bs) {
    int cnt = 0;
    for(auto &c : bs) {
        if(c == '1') {
            cnt++;
        }
    }
    return cnt;
}

int main() {
    std::string bs;
    std::cin >> bs;
    std::cin >> c;

    init_factorial(3005);

    std::cout << (calculate(bs) + quick_pow(c, count(bs))) % mod << std::endl;

}
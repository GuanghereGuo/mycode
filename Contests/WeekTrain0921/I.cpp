//
// Created by guanghere on 2025/9/21.
//
#include <bits/stdc++.h>

std::bitset<1024> add(std::bitset<1024> a, std::bitset<1024> b) {
    std::bitset<1024> sum = a, carry = b;
    while (carry.any()) {
        auto temp = sum;
        sum = temp ^ carry;
        carry = (temp & carry) << 1;
    }
    return sum;
}

std::string to_binary(int n) {
    std::string r;
    while (n != 0) {
        r += (n % 2 == 0 ? "0" : "1");
        n /= 2;
    }
    std::reverse(r.begin(), r.end());
    return r;
}

int len(const std::bitset<1024>& bs) {
    std::string s = bs.to_string();
    size_t pos = s.find('1');
    return 1024 - pos;
}

int main() {
    std::string s, d, m;
    std::cin >> s >> d >> m;
    if (d.size() <= 10) {
        int d_val = std::bitset<1024>(d).to_ulong();
        if (s.size() >= d_val && m.size() >= d_val) {
            std::cout << "Infinite money!\n";
            return 0;
        }
        int cnt = 0;
        std::bitset<1024> m_bit(m), s_bit(s);
        while (m_bit.any()) {
            int tmp = len(m_bit);
            if (tmp < d_val) {
                std::cout << to_binary(tmp + cnt) << '\n';
                return 0;
            }
            m_bit >>= d_val;
            m_bit = add(m_bit, s_bit);
            cnt += d_val;
        }
        std::cout << to_binary(cnt) << '\n';
    } else {
        std::cout << to_binary(m.size()) << '\n';
    }
}

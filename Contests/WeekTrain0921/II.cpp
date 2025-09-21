//
// Created by guanghere on 2025/9/21.
//
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>

int compare(const std::string& a, const std::string& b) {
    if (a.length() != b.length()) {
        return a.length() > b.length() ? 1 : -1;
    }
    if (a == b) return 0;
    return a > b ? 1 : -1;
}

std::string add(std::string a, std::string b) {
    std::string res = "";
    int i = a.length() - 1, j = b.length() - 1, carry = 0;
    while (i >= 0 || j >= 0 || carry) {
        int sum = carry;
        if (i >= 0) sum += a[i--] - '0';
        if (j >= 0) sum += b[j--] - '0';
        res += std::to_string(sum % 2);
        carry = sum / 2;
    }
    std::reverse(res.begin(), res.end());
    return res;
}

std::string shift_right(const std::string& a, long long n) {
    if (n >= a.length()) return "0";
    return a.substr(0, a.length() - n);
}

long long bin_to_ll(const std::string& bin) {
    if (bin.length() > 63) {
        throw std::overflow_error("Binary string too large for long long");
    }
    long long res = 0;
    for (char c : bin) {
        res = (res << 1) | (c - '0');
    }
    return res;
}

std::string ll_to_bin(long long n) {
    if (n == 0) return "0";
    std::string binary_string = "";
    while (n > 0) {
        binary_string += (n % 2 == 0 ? "0" : "1");
        n /= 2;
    }
    std::reverse(binary_string.begin(), binary_string.end());
    return binary_string;
}


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::string s, d, m;
    std::cin >> s >> d >> m;

    if (m == "0") {
        std::cout << "1\n";
        return 0;
    }

    bool d_is_small = (d.length() <= 63);

    if (d_is_small) {
        long long d_val = bin_to_ll(d);
        if (s.length() >= d_val && m.length() >= d_val) {
            std::cout << "Infinite money!\n";
            return 0;
        }

        std::string ans = "0";
        while (m != "0") {
            long long m_len = m.length();
            if (m_len <= d_val) {
                ans = add(ans, ll_to_bin(m_len));
                break;
            }
            m = shift_right(m, d_val);
            m = add(m, s);
            ans = add(ans, d);
        }
        std::cout << ans << '\n';

    } else {
        std::string s_len_str = ll_to_bin(s.length());
        std::string m_len_str = ll_to_bin(m.length());

        if (compare(s_len_str, d) >= 0 && compare(m_len_str, d) >= 0) {
            std::cout << "Infinite money!\n";
        } else {
            std::cout << m_len_str << '\n';
        }
    }

    return 0;
}

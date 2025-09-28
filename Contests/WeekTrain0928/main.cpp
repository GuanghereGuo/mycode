//
// Created by guanghere on 2025/9/28.
//
#include <bits/stdc++.h>
using int128 = __int128_t;

int128 gcd(int128 x, int128 y) {
    return std::gcd(x, y);
}

void generate(int128 n, std::map<int128, std::vector<int128>>& mp) {
    std::string s = std::to_string((long long)n);
    int128 len = s.size();
    for (int128 i = 1; i < (1 << len); ++i) {
        std::string sub_s;
        for (int128 j = 0; j < len; ++j) {
            if ((i >> j) & 1) {
                sub_s += s[j];
            }
        }

        if (sub_s[0] == '0') {
            continue;
        }

        int128 cur_n = std::stoll(sub_s);
        std::vector<int128> cnt(10, 0);
        for (char c : sub_s) {
            cnt[c - '0']++;
        }
        mp[cur_n] = cnt;
    }
}

signed main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    long long a1, b1, c1, d1;
    std::cin >> a1 >> b1 >> c1 >> d1;

    int128 a = a1, b = b1, c = c1, d = d1;

    if ((int128)a * d1 == (int128)b * c) {
        std::cout << "possible\n";
        std::cout << (long long)a << " " << (long long)b << "\n";
        return 0;
    }

    int128 g = gcd(c, d1);
    int128 cc = c / g;
    int128 dd = d1 / g;

    std::map<int128, std::vector<int128>> mpa;
    generate(a, mpa);

    std::string sa = std::to_string((long long)a);
    std::string sb = std::to_string((long long)b);

    std::vector<int128> ca(10, 0), cb(10, 0);
    for (char ch : sa) ca[ch - '0']++;
    for (char ch : sb) cb[ch - '0']++;

    int128 len_b = sb.size();
    for (int128 i = 1; i < (1 << len_b); ++i) {
        std::string sub_s;
        for (int128 j = 0; j < len_b; ++j) {
            if ((i >> j) & 1) {
                sub_s += sb[j];
            }
        }

        if (sub_s[0] == '0') {
            continue;
        }

        int128 bp = std::stoll(sub_s);

        int128 num = (int128)bp * cc;
        if (num % dd != 0) {
            continue;
        }
        int128 ap_req = (int128)(num / dd);

        if (mpa.count(ap_req)) {
            const auto& cap = mpa[ap_req];
            std::vector<int128> cbp(10, 0);
            for (char ch : sub_s) cbp[ch - '0']++;

            bool ok = true;
            for (int128 k = 0; k < 10; ++k) {
                if (ca[k] - cb[k] != cap[k] - cbp[k]) {
                    ok = false;
                    break;
                }
            }

            if (ok) {
                std::cout << "possible\n";
                std::cout << (long long)ap_req << " " << (long long)bp << "\n";
                return 0;
            }
        }
    }

    std::cout << "impossible\n";

    return 0;
}

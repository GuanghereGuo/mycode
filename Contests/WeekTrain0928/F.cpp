//
// Created by guanghere on 2025/9/28.
//
#include <bits/stdc++.h>

using int128 = __int128;

int128 gcd(int128 x, int128 y) {
    if (x % y == 0) {
        return y;
    }
    return gcd(y, x % y);
}

void for_each_subsequence(int128 n, const std::function<void(int128, const std::vector<int128>&)>& callback) {
    std::string s = std::to_string((long long)n);
    int128 len = s.length();
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
        callback(cur_n, cnt);
    }
}

signed main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    long long a1, b1, c1, d1;
    std::cin >> a1 >> b1 >> c1 >> d1;

    int128 a = a1, b = b1, c = c1, d = d1;

    int128 g = gcd(c, d);
    int128 cc = c / g;
    int128 dd = d / g;

    std::map<int128, std::vector<int128>> mpa;
    for_each_subsequence(a, [&](int128 ap, const std::vector<int128>& cap) {
        mpa[ap] = cap;
    });
    std::vector<int128> ca(10, 0), cb(10, 0);
    for (char ch : std::to_string((long long)a)) ca[ch - '0']++;
    for (char ch : std::to_string((long long)b)) cb[ch - '0']++;

    bool found = false;
    int128 final_ap = 0, final_bp = 0;

    for_each_subsequence(b, [&](int128 bp, const std::vector<int128>& cbp) {
        if (found) return;

        int128 num = (int128)bp * cc;
        if (num % dd != 0) {
            return;
        }
        int128 ap_req = (int128)(num / dd);

        if (mpa.count(ap_req)) {
            const auto& cap = mpa.at(ap_req);

            bool ok = true;
            for (int128 k = 0; k < 10; ++k) {
                if (ca[k] - cb[k] != cap[k] - cbp[k]) {
                    ok = false;
                    break;
                }
            }

            if (ok) {
                found = true;
                final_ap = ap_req;
                final_bp = bp;
            }
        }
    });

    if (found) {
        std::cout << "possible\n";
        std::cout << (long long)final_ap << " " << (long long)final_bp << "\n";
    } else {
        std::cout << "impossible\n";
    }

    return 0;
}

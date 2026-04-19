//
// Created by guanghere on 2026/4/19.
//
#include <bits/stdc++.h>

#define int long long

signed main() {
    int t;
    std::cin >> t;

    while (t--) {
        int n;
        std::cin >> n;


        std::string s;
        std::cin >> s;
        std::vector<bool> single;

        if (n == 1 || n == 2) {
            std::cout << "0\n";
            continue;
        }

        if (s[0] != s[1]) {
            single.push_back(true);
        }
        for (int i = 2; i < n; i++) {
            if (s[i] != s[i - 1]) {
                single.push_back(s[i] == s[i - 2]);
            }
        }
        single.push_back(s[n - 1] != s[n - 2]);

        bool flag = true;


        int len = single.size();
        int mid = len / 2;

        for (int i = 0; i < len; i++) {
            if (single[i] == 0) {
                flag = false;
            }
        }
        if (flag) {
            std::cout << "0\n";
            continue;
        }

        // // max
        // int maxlen , minlen = INT_MAX;
        // for (int offset = 0; offset < len; offset++) {
        //     if (!single[offset] || !single[len - offset - 1]) {
        //         maxlen = len - offset ;
        //         break;
        //     }
        // }

        std::vector<int> pos;
        for (int i = 0; i < len; i++) {
            if (!single[i]) {
                pos.push_back(i);
            }
        }

        if (pos.empty()) {
            std::cout << "0\n";
            continue;
        }

        int pref = pos.front();
        int suff = len - 1 - pos.back();

        int max_gap = 0;
        for (int i = 1; i < (int)pos.size(); i++) {
            max_gap = std::max(max_gap, pos[i] - pos[i - 1] - 1);
        }

        int maxlen = len - std::min(pref, suff);

        int need_mid = 0;
        if (pos.size() >= 2) {
            need_mid = max_gap + 1;
        }

        int minlen = 1 + std::max({len / 2, pref, suff, need_mid});


        // // min from mid
        // for (int offset = 0; mid - offset >= 0; offset++) {
        //     if (!single[mid - offset]) {
        //         minlen = std::min(minlen, std::max(len - (mid - offset), mid - offset + 1));
        //         break;
        //     }
        // }

        // //print single
        // std::cout << "single:\n";
        // for (int i = 0; i < single.size(); i++) {
        //     std::cerr << single[i];
        // }
        // std::cerr << std::endl;

        for (int offset = 0; offset < len; offset++) {
            if (!single[offset]) {
                minlen = std::min(minlen, std::max(len - (offset), offset + 1));
            }
        }

        // std::cerr << len << " " << minlen <<  " " << maxlen << std::endl;
        std::cout << maxlen - minlen << '\n';

        // //test output
        // for (int i = 0; i < single.size(); i++) {
        //     std::cout << single[i];
        // }
        // std::cout << std::endl;

    }
}
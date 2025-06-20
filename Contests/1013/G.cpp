//
// Created by 24087 on 24-10-13.
//
#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::vector<int> vec = {1, 0};
    int t, maxn = 0;
    std::cin >> t;
    std::vector<int> qes;

    for(int i = 1; i <= t; i++) {
        int n;
        std::cin >> n;
        maxn = std::max(maxn, n);
        qes.emplace_back(n);
    }

    std::vector<bool> ans(maxn + 1);

    ans[0] = false;
    ans[1] = true;

    for(int i = 2, x = 1; i <= maxn; i++) {
        if(ans[i - 1]) {
            x ^= i;
            if(x == 0) {
                ans[i] = false;
            } else {
                ans[i] = true;
                vec.push_back(i);
            }
        } else {
            ans[i] = true;
            x ^= i;
            vec.push_back(i);
            vec.push_back(i - 1);
        }
    }
    for (const int i : qes) {
        if(!ans[i - 1]) {
            std::cout << "impossible\n";
            continue;
        }
        for(int j = 0; j < i; j++) {
            std::cout << vec[j] << ' ';
        }
        std::cout << '\n';
    }
}
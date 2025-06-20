//
// Created by 24087 on 24-10-9.
//
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

bool check(std::string &&str) {
    auto reversed  = str;
    std::reverse(reversed.begin(), reversed.end());
    if(str != reversed) {
        return false;
    }
    return true;
}

bool check(int i, int k) {
    if(!check(std::to_string(i))) {
        return false;
    }
    std::string base_k;
    while(i > 0) {
        base_k.push_back(i % k + '0');
        i /= k;
    }
    return check(std::move(base_k));
}

int main() {
    int k, n;
    std::cin >> n >> k;
    int ans = 0;
    for(int i = 1; i <= n; i++) {
        if(check(i, k)) {
            ans += i;
        }
    }
    std::cout << ans;
}
//
// Created by 24087 on 24-9-28.
//
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

int main() {
    int n;
    std::cin >> n;
    std::vector<int> vec(n);
    for(int i = 0; i < n; i++) {
        std::cin >> vec[i];
    }
    std::sort(vec.begin(), vec.end());
    int ans = INT_MAX;
    for(int i = 0; i < n - 1; i++) {
        ans = std::min(ans, vec[i + 1] - vec[i]);
    }
    std::cout << ans;
}
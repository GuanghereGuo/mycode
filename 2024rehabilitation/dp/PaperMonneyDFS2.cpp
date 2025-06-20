//
// Created by 24087 on 9/10/2024.
//
#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

int n, target, ans = INT_MAX;
std::vector<int> vec;

int dfs(int dep, int sum) {
    if(sum == 0) {
        return 0;
    }
    if(sum < 0) {
        return INT_MAX;
    }

    int min_n = INT_MAX;

    for (int val : vec) {
        min_n = std::min(dfs(dep + 1, sum - val), );
    }
}

int main() {
    std::cin >> n >> target;
    vec.resize(n);

    for(int i = 0; i < n; i++) {
        std::cin >> vec[i];
    }
    std::ranges::reverse(vec);

    std::cout << ans;
}

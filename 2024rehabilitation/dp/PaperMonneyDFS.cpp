//
// Created by 24087 on 9/10/2024.
//
#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

int n, target, ans = INT_MAX;
std::vector<int> vec;

void dfs(const int depth, const int sum) {
    if(depth >= ans)
        return;
    if(sum > target)
        return;
    if(sum == target) {
        ans = std::min(ans, depth);
        return;
    }
    for(int value : vec) {
        dfs(depth + 1, sum + value);
    }
}

int main() {
    std::cin >> n >> target;
    vec.resize(n);

    for(int i = 0; i < n; i++) {
        std::cin >> vec[i];
    }
    std::ranges::reverse(vec);

    dfs(0, 0);

    std::cout << ans;
}

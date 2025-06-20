//
// Created by 24087 on 24-10-5.
//

#include <iostream>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, k;
    std::cin >> n >> k;

    std::vector<bool> vis(n + 1);
    std::vector<int> ans;

    for(int i = 1; i <= k; i++) {
        for(int j = i; j <= n; j += k) {
            if(vis[j])
                continue;
            vis[j] = true;
            ans.emplace_back(j);
        }
    }
    for(int i : ans) {
        if(i == ans.back())
            continue;
        std::cout << i << ' ';
    }
    std::cout << ans.back();
}
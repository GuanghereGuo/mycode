//
// Created by 24087 on 9/5/2024.
//

#include <iostream>
#include <vector>

class Solution {
    int n;
    std::vector<int> vec, reachable;
    std::vector<bool> vis;
    std::string flag;

    int get_reachable(int x) {
        if(vis[x]) {
            return 0;
        }
        vis[x] = true;
        if(reachable[x]) {
            return reachable[x];
        }
        if(flag[x] == '1')
            return reachable[x] = get_reachable(vec[x]);
        else
            return reachable[x] = get_reachable(vec[x]) + 1;
    }
public:
    Solution() {
        std::cin >> n;
        vec.resize(n + 1);
        vis.resize(n + 1);
        reachable.resize(n + 1);
        for(int i = 1; i <= n; i++) {
            std::cin >> vec[i];
        }
        std::cin >> flag;
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int t;
    std::cin >> t;
    while(t--) {

    }
}

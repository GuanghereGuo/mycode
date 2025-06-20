//
// Created by guanghere on 25-4-6.
//
#include <iostream>
#include <ranges>
#include <vector>

// // 求逆序对
auto get_inverse_pair(int n, const std::vector<int>& v) -> int {
    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            ans++;
            if (v[i] < v[j]) {
                ans++;
            }
        }
    }
    return ans;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int n;
    std::cin >> n;
    std::vector<int> v(n + 1);
    for (int i = 1; i <= n; ++i) {
        std::cin >> v[i];
    }

    //std::cout << get_inverse_pair(n, v) << std::endl;
    std::cerr << get_inverse_pair(n, v) << std::endl;
    std::vector<std::vector<int>> g(n + 1, std::vector<int>(n + 1, 0));
    for (int i = 1; i <= n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            if (v[i] < v[j]) {
                g[v[i]][v[j]]=1;
            }
        }
    }
    std::vector<std::pair<int, int>> ans;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j < n; ++j) {
            if (g[v[j]][v[j+1]]==1) {
                //std::cout<<v[j]<<" "<<v[j+1]<<std::endl;
                //std::cout<<v[j+1]<<" "<<v[j]<<std::endl;
                ans.emplace_back(v[j], v[j+1]);
                ans.emplace_back(v[j + 1], v[j]);
                g[v[j]][v[j+1]] = 0;
            }
        }
        for (int j = 1; j < n; ++j) {
            if (v[j]>v[j + 1]) {
                //std::cout<<v[i]<<" "<<v[j]<<std::endl;
                ans.emplace_back(v[j], v[j + 1]);
                std::swap(v[j], v[j + 1]);
            }
        }
    }
    std::cout << ans.size() << std::endl;
    for (int i = (int)ans.size() - 1; i >= 0; --i) {
        std::cout << ans[i].first << " " << ans[i].second << std::endl;
    }
}
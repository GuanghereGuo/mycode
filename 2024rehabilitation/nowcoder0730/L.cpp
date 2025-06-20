//
// Created by 24087 on 24-7-30.
//
#include <iostream>
#include <vector>
#include <queue>

constexpr int mod = 998244353;

class Solution {
    int n;
    std::vector<int> a;
public:
    explicit Solution(int _n, std::vector<int> _a):n(_n), a(std::move(_a)){}
    int get_max_product() {
        std::priority_queue<int,std::vector<int>, std::greater<>> qu;
        qu.push(a[1]);
        for(int i = 2; i <= n; i++) {
            int now = a[i];
            while(now - 1 > qu.top()) {
                qu.push(qu.top() + 1);
                qu.pop();
                now--;
            }
            qu.push(now);
        }

        long long product = 1;
        while(!qu.empty()) {
            product = ( product * qu.top() ) % mod;
            qu.pop();
        }
        return product;
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);

    int T;
    std::cin >> T;
    while(T--) {
        int n;
        std::cin >> n;
        std::vector<int> a(n + 1);
        for(int i = 1; i <= n; i++) {
            std::cin >> a[i];
        }
        Solution ans(n, std::move(a));
        std::cout << ans.get_max_product() <<'\n';
    }
}

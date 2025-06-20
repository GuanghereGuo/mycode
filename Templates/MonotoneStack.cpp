//
// Created by 24087 on 24-10-21.
//
#include <iostream>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n;
    std::cin >> n;
    std::vector<int> stk, vec(n + 1);
    for(int i = 1; i <= n; ++i) {
        std::cin >> vec[i];
    }

    long long ans = 0;

    for(int i = n; i > 0; i--) {
        while(!stk.empty() && vec[stk.back()] < vec[i]) {//牛只能看到比自己矮的，所以要找第一个>=自己的
            stk.pop_back();
        }
        ans += stk.empty() ? n - i : stk.back() - i - 1;//居然看不到最高的那个牛
        stk.push_back(i);
    }
    std::cout << ans;
}
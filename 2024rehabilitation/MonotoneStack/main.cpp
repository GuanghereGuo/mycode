#include <iostream>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n;
    std::cin >> n;
    std::vector<int> stk, vec(n + 1), ans(n + 1);
    for(int i = 1, x; i <= n; ++i) {
        std::cin >> vec[i];
    }
    for(int i = n; i > 0; i--) {
        while(!stk.empty() && vec[stk.back()] <= vec[i]) {
            stk.pop_back();
        }
        ans[i] = stk.empty() ? 0 : stk.back();
        stk.push_back(i);
    }
    for(int i = 1; i <= n; ++i) {
        std::cout << ans[i] << ' ';
    }
}

#include <iostream>
#include <vector>

int binary_search(int destination, const std::vector<int> &vec) {
    int l = 0, r = static_cast<int>(vec.size());//n + 1
    while(l + 1 < r) {
        int mid = (l + r) / 2;
        if(vec[mid] < destination) {
            l = mid;
        } else {
            r = mid;
        }
    }
    return r;
}
//此方法是在讲期望l指向满足条件最后一个，r期望指向不满足条件第一个

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, m;
    std::cin >> n >> m;
    std::vector<int> vec(n + 1);
    for(int i = 1; i <= n; i++) {
        std::cin >> vec[i];
    }
    for(int i = 1; i <= m; i++) {
        int x;
        std::cin >> x;
        int result = binary_search(x, vec);
        if(result == vec.size() || vec[result] != x) {
            std::cout << -1 << ' ';
        } else {
            std::cout << result << ' ';
        }
    }
}

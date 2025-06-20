#include <iostream>
#include <vector>

int binary_search(int destination, const std::vector<int> &vec) {
    int l = 0, r = static_cast<int>(vec.size()) - 1;
    // 全都不满足条件，归0，区间外
    //全都满足就是最后一个，区间内
    while(l < r) {
        int mid = (l + r + 1) / 2;//attention
        if(vec[mid] < destination) {
            l = mid;
        } else {
            r = mid - 1;
        }
    }
    return r;
}
//此方法是在讲，期望l，r都指向满足条件的最后一个

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
        if(result == vec.size() - 1 || vec[result + 1] != x) {
            std::cout << -1 << ' ';
        } else {
            std::cout << result + 1<< ' ';
        }
    }
}

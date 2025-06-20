//
// Created by guanghere on 24-12-23.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

template<typename T>
void discretization_binary(std::vector<T> &a) {
    a[0] = std::numeric_limits<T>::min();
    std::vector<T> vec = a;
    std::sort(vec.begin(), vec.end());
    vec.erase(std::unique(vec.begin(), vec.end()), vec.end());
    for (auto &i : a) {
        i = std::lower_bound(vec.begin(), vec.end(), i) - vec.begin();
    }
}


//诶，还不是第几名
template<typename T>
void discretization_linear(std::vector<T> &a) {
    a[0] = std::numeric_limits<T>::min();
    struct Node {
        T val;
        int id;
        bool operator<(const Node &rhs) const { return val < rhs.val; }
    };
    std::vector<Node> vec;
    for (int i = 0; i < a.size(); i++) {
        vec.push_back({a[i], i});
    }
    std::sort(vec.begin(), vec.end());
    for (int i = 0, cnt = 0; i < vec.size(); i++) {
        a[vec[i].id] = cnt;
        if (i + 1 < vec.size() && vec[i].val != vec[i + 1].val) {
            cnt++;
        }
    }
}

void solve() {
    int n;
    std::cin >> n;
    std::vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i];
    }
    //discretization_binary(a);
    discretization_linear(a);
    for (int i = 1; i <= n; i++) {
        std::cout << a[i] << ' ';
    }
    std::cout << '\n';
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }
}

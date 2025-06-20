//
// Created by guanghere on 25-6-3.
//
#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>


int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t;
    std::cin >> t;
    while (t--) {
        int n, m;
        std::cin >> n >> m;
        std::vector<long long> a(m);
        for(int i = 0; i < m; i++) {
            std::cin >> a[i];
        }
        std::vector<int> idx(m);
        for(int i = 0; i < m; i++) {
            idx[i] = i;
        }
        sort(idx.begin(), idx.end(), [&](int x, int y) {
            return a[x] / 100 < a[y] / 100;
        });
        for(int i = 0; i < n / 2; i++) {
            std::cout << a[idx[i]] << " " << a[idx[m-1-i]] << " "
                 << a[idx[i]] << " " << a[idx[m-1-i]] << " "
                 << a[idx[i]] << " " << a[idx[m-1-i]] << "\n";
            std::cout << a[idx[m-1-i]] << " " << a[idx[i]] << " "
                 << a[idx[m-1-i]] << " " << a[idx[i]] << " "
                 << a[idx[m-1-i]] << " " << a[idx[i]] << "\n";
        }
        if (n % 2 == 1) {
            int i = n / 2;
            std::cout << a[idx[i]] << " " << a[idx[m-1-i]] << " "
                 << a[idx[i]] << " " << a[idx[m-1-i]] << " "
                 << a[idx[i]] << " " << a[idx[m-1-i]] << "\n";
        }
    }
    return 0;
}
//
// Created by 24087 on 24-10-13.
//
#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

int main() {
    int N;
    std::cin >> N;
    for(int n = 1; n <= N; n++) {
        std::vector<int> v(n);
        std::iota(v.begin(), v.end(), 0);
        std::cout << n << ": ";
        do {
            int x = v[0];
            if(x == 0) {
                continue;
            }
            bool flag = true;
            for(int i = 1; i < n; i++) {
                x ^= v[i];
                if(x == 0) {
                    flag = false;
                    break;
                }
            }
            if(flag) {
                for(int i = 0; i < n; i++) {
                    std::cout << v[i] << ' ';
                }
                break;
            }
        } while (std::next_permutation(v.begin(), v.end()));
        std::cout << std::endl;
    }
}
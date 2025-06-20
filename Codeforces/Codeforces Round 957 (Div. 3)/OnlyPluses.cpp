//
// Created by 24087 on 24-7-24.
//

#include <iostream>
#include <array>
#include <algorithm>

class OnlyPluses {
    std::array<int, 4> a = {0};
public:
    void run() {
        for(int i = 1; i <= 3; i++) {
            std::cin >> a[i];
        }
        int cnt = 5;
        while(cnt--) {
            std::sort(a.begin() + 1, a.end());
            a[1]++;
        }
        std::cout << a[1] * a[2] * a[3] << '\n';
    }
};

int main() {
    std::ios::sync_with_stdio(false);

    int t;
    std::cin >> t;
    while (t--) {
        OnlyPluses solution;
        solution.run();
    }
}

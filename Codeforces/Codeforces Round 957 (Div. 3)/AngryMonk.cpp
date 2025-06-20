//
// Created by 24087 on 24-7-25.
//

#include <iostream>
#include <vector>

class AngryMonk {
    int n = 0, k = 0;
    // std::vector<int> vec;
public:
    void run() {
        std::cin >> n >> k;
        // vec.resize(n + 1);

        int max_n = 0;

        for(int i = 1; i <= k; i++) {
            int tmp;
            std::cin >> tmp;
            if(tmp > max_n) {
                max_n = tmp;
            }
        }

        std::cout << (n - k) - (max_n - 1) + (n - max_n) << '\n';

    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int t;
    std::cin >> t;
    while(t--) {
        AngryMonk solution;
        solution.run();
    }
}

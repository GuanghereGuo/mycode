//
// Created by 24087 on 24-10-15.
//
#include <iostream>
#include <vector>
#include <climits>

//init factorials
std::vector<unsigned long long> factorials = {1, 1};
void init_factorials(int n) {
    for (int i = 2; i <= n; ++i)
        factorials.push_back(factorials[i - 1] * i);
}

unsigned long long C(int n, int m) {
    if(n <= 0 || m <= 0 || n < m) {
        return 0;
    }
    return factorials[n] / factorials[m] / factorials[n - m];
}


int main() {
    int x1, y1, x2, y2;
    init_factorials(1000);
    std::cin >> x1 >> y1 >> x2 >> y2;
    while(x1 > 0  && x2 > 0 && y1 > 0 && y2 > 0) {
        x1--;
        y1--;
        x2--;
        y2--;
        if(x1 == x2 && y1 == y2) {
            std::cout << 0 << std::endl;
            std::cin >> x1 >> y1 >> x2 >> y2;
            continue;
        }
        if(x2 > x1 || y2 > y1) {
            std::cout << C(x1 + y1, x1) << std::endl;
            std::cin >> x1 >> y1 >> x2 >> y2;
            continue;

        }
        int dx = x2 - x1;
        int dy = y2 - y1;
        std::cout << static_cast<int>(C(x1 + y1, x1) - C(x2 + y2, x2) * C(dx + dy, dx)) << std::endl;
        std::cin >> x1 >> y1 >> x2 >> y2;
    }
}
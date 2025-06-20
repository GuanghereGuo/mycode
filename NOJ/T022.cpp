//
// Created by 24087 on 24-10-5.
//
#include <iostream>
#include <vector>

int main() {
    int n;
    std::cin >> n;
    int ans = 0;
    for(int i = n; i >= 1; i--) {
        int now = i, sum = n;
        while(now >= 1 && sum >= 0) {
            sum -= now;
            now--;
            if(sum == 0) {
                ans++;
                break;
            }
        }
    }
    std::cout << ans;
}
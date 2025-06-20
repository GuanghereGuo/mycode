//
// Created by 24087 on 24-10-5.
//
#include <iostream>

int main() {
    int n;
    std::cin >> n;
    for(int i = 1, mod = 1, cnt = 1; ; i++) {
        if(cnt == n) {
            std::cout << i << '\n';
            break;
        }
        if(i == mod) {
            i = 1;
            mod++;
        }
        cnt++;
    }
}

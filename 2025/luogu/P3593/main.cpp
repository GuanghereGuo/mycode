//
// Created by guanghere on 25-2-24.
//
#include <iostream>
#include <cstring>


int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int a[100];
    std::memset(a, 0x3f3f3f3f, 10*sizeof(int));
    for (int i = 0; i < 10; ++i) {
        std::cout << a[i] << " ";
    }
}

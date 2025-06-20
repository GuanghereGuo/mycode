//
// Created by 24087 on 24-10-15.
//
//quick_sort
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int n;
    std::cin >> n;
    std::vector<int> vec(n);
    for (int i = 0; i < n; ++i)
        std::cin >> vec[i];
    std::sort(vec.begin(), vec.end());
    for (int i = 0; i < n; ++i)
        std::cout << vec[i] << " ";
    return 0;
}
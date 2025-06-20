//
// Created by 24087 on 24-10-7.
//
#include <iostream>
#include <initializer_list>

template<typename T>
T sum(const T &t) {
    return t;
}

template<typename T, typename... Args>
T sum(const T &t, const Args&... args) {
    return t + sum<T>(args...);
}

int main() {
    int a, b, c, d, e, f;
    std::cin >> a >> b >> c >> d >> e >> f;
    std::cout << sum(a, b) - sum(c, d, e, f);
}
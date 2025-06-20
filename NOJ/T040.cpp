//
// Created by 24087 on 24-10-7.
//
//
// Created by 24087 on 24-10-7.
//
#include <initializer_list>
#include <iomanip>
#include <iostream>

template <typename T>
T sum(const T &t) {
    return t;
}

template<typename T, typename... Args>
T sum(const T &t, const Args&... args) {
    return t + sum<T>(args...);
}

template<typename... Args>
double average(const Args&... args) {
    return static_cast<double>(sum(args...)) / sizeof...(args);
}

int main() {
    int a, b, c, d, e;
    std::cin >> a >> b >> c >> d >> e;
    std::cout << std::fixed << std::setprecision(4) << average(a, b) - average(c, d, e);
}
#include <cmath>
#include <iostream>

double get_num (int n) {
    double m = static_cast<double>(n) + 1;
    while (floor(m)) {
        m /= 10;
    }
    return m + n;
}

int main() {
    int n;
    std::cin >> n;
    double sum = 0, num;

    for (int i = 1; i < n; i++) {
        num = get_num(i);
        sum += num;
        printf("%g+", num);
    }

    num = get_num(n);
    sum += num;
    printf("%g=%g", num, sum);
}
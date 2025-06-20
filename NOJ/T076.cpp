//
// Created by 24087 on 24-10-16.
//
#include <cmath>
#include <iomanip>
#include <iostream>

int main() {
    const double pi = 3.1415926;
    double a, b, c, d, diag;

    std::cin >> a >> b >> c >> d >> diag;

    double p = (a + b + diag) / 2;
    double q = (c + d + diag) / 2;
    double s = sqrt(p * (p - a) * (p - b) * (p - diag)) + sqrt(q * (q - c) * (q - d) * (q - diag));

    double angle = atan((4 * s) / (pow(b, 2) + pow(d, 2) - pow(a, 2) - pow(c, 2)));
    angle *= 180 / pi;

    std::cout << std::fixed << std::setprecision(6) << s << " " << std::fixed << std::setprecision(1) << angle;

    return 0;
}

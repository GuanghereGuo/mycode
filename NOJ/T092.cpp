//
// Created by 24087 on 24-10-8.
//
#include <cmath>
#include <iomanip>
#include <iostream>

void mach(double v, double T) {
    double m = (v / 3.6) / (331.3 * std::sqrt(1 + T / 273.15));
    std::cout << std::fixed << std::setprecision(3) << m << " ";
    if (m - 0.8 < 1e-6)
        std::cout << "subsonic\n";
    else if (m - 1.2 < 1e-6)
        std::cout << "transonic\n";
    else if (m - 5.0 < 1e-6)
        std::cout << "supersonic\n";
    else
        std::cout << "hypersonic\n";
}

int main() {
    double v, T;
    std::cin >> v >> T;
    mach(v, T);
    return 0;
}
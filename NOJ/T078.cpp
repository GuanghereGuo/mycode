//
// Created by 24087 on 24-10-16.
//
#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>
#include <array>

struct Atom {
    std::string name;
    double mass;
    double APF;
    double r;
};

Atom elemList[] = {
    {"Po", 208.998, 0.52360, 1.68},   {"Li", 6.941, 0.68017, 1.52},
    {"Na", 22.989770, 0.68017, 1.86}, {"Cr", 51.9961, 0.68017, 1.28},
    {"Mn", 54.938049, 0.68017, 1.27}, {"Fe", 55.845, 0.68017, 1.26},
    {"Mo", 95.94, 0.68017, 1.39},     {"Ta", 180.9749, 0.68017, 1.46},
    {"Al", 26.981538, 0.74048, 1.43}, {"Ca", 40.078, 0.74048, 1.97},
    {"Ni", 58.6934, 0.74048, 1.24},   {"Cu", 63.546, 0.74048, 1.28},
    {"Ge", 72.64, 0.74048, 1.22},     {"Ag", 107.8682, 0.74048, 1.44},
    {"Pt", 195.078, 0.74048, 1.39},   {"Au", 196.96655, 0.74048, 1.44},
    {"Pb", 207.2, 0.74048, 1.75}};


constexpr double pow(double a, int k) {
    if(k == 0)
        return 1;
    return a * pow(a, k - 1);
}


int main() {
    int n;
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        std::string in;
        std::cin >> in;
        for (const auto& e : elemList) {
            if (e.name == in) {
                double V = 4.0 * M_PI * pow<3>(e.r) / 3.0;
                std::cout << std::fixed << std::setprecision(2)
                          << 10.0 * e.mass * e.APF / 6.022 / V << std::endl;
                break;
            }
        }
    }
}
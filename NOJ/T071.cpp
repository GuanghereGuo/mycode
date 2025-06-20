//
// Created by 24087 on 9/10/2024.
//
#include <iomanip>
#include <iostream>

int main() {
    int ti, tf;
    double m1, c1, m2, c2;
    std::cin >> ti >> tf >> m1 >> c1 >> m2 >> c2;
    double e1 = c1 * m1 * (tf - ti);
    double e2 = c2 * m2 * (tf - ti);
    // std::cout
    //     << std::format("{:.2f}KJ,{:.2f},{:.2f}", (e1 + e2)/1000, e2/(e1 + e2), e1/(e1 + e2));
    std::cout << std::fixed << std::setprecision(2) << (e1 + e2)/1000 << "kJ," << e2/(e1 + e2) << "%," << e1/(e1 + e2) << "%";
}

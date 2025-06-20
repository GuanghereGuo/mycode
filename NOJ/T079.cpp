//
// Created by 24087 on 24-10-16.
//
#include <iomanip>
#include <iostream>

constexpr double time_step = 0.1;

int main() {
    double total_mass, rocket_mass, burn_time, c_e, g;
    std::cin >> total_mass >> rocket_mass >> burn_time >> c_e >> g;
    double propellant_mass = total_mass - rocket_mass;
    double mass_flow = propellant_mass / burn_time;
    double T = mass_flow * c_e;
    double altitude = 0, V = 0;
    double time_left = burn_time + time_step;
    while (time_left >= 0) {
        double a = T / total_mass;
        double delta_v = a * time_step;
        double delta_altitude = V * time_step;
        double delta_m = mass_flow * time_step;
        V += delta_v;
        altitude += delta_altitude;
        total_mass -= delta_m;
        time_left -= time_step;
    }
    std::cout << std::fixed << std::setprecision(3) << altitude / 1000 << "km"
              << std::endl;
}
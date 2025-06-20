//
// Created by 24087 on 24-10-8.
//
#include <iostream>
#include <cmath>
#include <vector>
#include <limits>
#include <iomanip>

struct Plane {
    std::string id;
    int x{};
    int y{};
};

int main() {
    int n;
    std::cin >> n;
    std::vector<Plane> planes(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> planes[i].id >> planes[i].x >> planes[i].y;
    }

    double minDist = std::numeric_limits<double>::max();
    int idx1 = 0, idx2 = 0;
    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            double dist = std::sqrt(std::pow(planes[i].x - planes[j].x, 2) +
                                    std::pow(planes[i].y - planes[j].y, 2));
            if (dist < minDist) {
                idx1 = i;
                idx2 = j;
                minDist = dist;
            }
        }
    }
    std::cout << planes[idx1].id << "-" << planes[idx2].id << " " << std::fixed << std::setprecision(4) << minDist << std::endl;
}

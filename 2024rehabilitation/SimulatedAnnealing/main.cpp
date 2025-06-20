#include <cmath>
#include <iomanip>
#include <iostream>
#include <random>
#include <vector>

struct Stuff {
    int x = 0, y = 0, w = 0;
};

class SimulatedAnnealing {
    int n;
    std::vector<Stuff> vec;
    int max_x = 0, max_y = 0, min_x = 1e9, min_y = 1e9;
    double best_x = 0, best_y = 0,
           best_energy = std::numeric_limits<double>::max();

    static double get_distance(const double x1, const double y1,
                               const double x2, const double y2) {
        return std::sqrt(std::pow(x1 - x2, 2) + std::pow(y1 - y2, 2));
    }

    double get_potential_energy(const double x, const double y) {
        double energy = 0;
        for (int i = 1; i <= n; i++) {
            energy += vec[i].w * get_distance(x, y, vec[i].x, vec[i].y);
        }
        return energy;
    }

    void simulated_annealing() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<double> gen_x(-max_x, max_x);
        std::uniform_real_distribution<double> gen_y(-max_y, max_y);
        double x = 0, y = 0;
        double energy = get_potential_energy(x, y);
        double t = 1000, t0 = t / 1000;
        double t_min = 1e-7;
        double alpha = 0.995;

        while (t > t_min) {
            double new_x = x + gen_x(gen) * t / t0;
            double new_y = y + gen_y(gen) * t / t0;
            if (new_x < -max_x || new_x > max_x || new_y < -max_y || new_y >
            max_y) {
                t *= alpha;
                continue;
            }
            double new_energy = get_potential_energy(new_x, new_y);
            if (new_energy < energy) {
                x = new_x;
                y = new_y;
                energy = new_energy;
                if (energy < best_energy) {
                    best_x = x;
                    best_y = y;
                    best_energy = energy;
                }
            } else {
                double p = std::exp((energy - new_energy) / t);
                if (std::uniform_real_distribution<double>(0, 1)(gen) < p) {
                    x = new_x;
                    y = new_y;
                    energy = new_energy;
                }
            }
            t *= alpha;
        }
    }

   public:
    SimulatedAnnealing(const int n, std::vector<Stuff> &&v)
        : n(n), vec(std::move(v)) {
        for (auto s : vec) {
            max_x = std::max(max_x, std::abs(s.x));
            max_y = std::max(max_y, std::abs(s.y));
            // min_x = std::min(min_x, s.x);
            // min_y = std::min(min_y, s.y);
        }
    }

    void calculate() {
        // for (int i = 1; i <= 20; i++)
        //     simulated_annealing();
        while ((double)clock() / CLOCKS_PER_SEC < 3) simulated_annealing();
        std::cout << best_x << ' ' << best_y << '\n';
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);

    std::cout << std::fixed << std::setprecision(3);

    int n;
    std::cin >> n;
    std::vector<Stuff> vec(n + 1);

    for (int i = 1; i <= n; i++) {
        std::cin >> vec[i].x >> vec[i].y >> vec[i].w;
    }

    SimulatedAnnealing sa(n, std::move(vec));
    sa.calculate();
}
#include <iostream>
#include <vector>
#include <cmath>

class Function {
    int n;
    std::vector<double> coefficients;
public:
    Function(const int n, std::vector<double> &&vec) : n(n), coefficients(std::move(vec)) {}
    double operator()(const double x) const {
        double result = 0;
        for (int i = 0; i <= n; i++) {
            result += coefficients[i] * pow(x, i);
        }
        return result;
    }
};

double get_max_point(const Function &f, const double L, const double R) {
    constexpr double eps = 1e-7;
    double l = L, r = R;
    while (r - l > eps) {
        const double mid = (l + r) / 2;
        if (f(mid - eps) > f(mid + eps)) {
            r = mid;
        } else {
            l = mid;
        }
    }
    return l;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n;
    double l, r;
    std::cin >> n >> l >> r;
    std::vector<double> coefficients(n + 1);
    for (int i = 0; i <= n; i++) {
        std::cin >> coefficients[n - i];
    }
    Function f(n, std::move(coefficients));

    std::cout << get_max_point(f, l, r) << std::endl;
}

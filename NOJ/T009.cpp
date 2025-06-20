#include <cmath>
#include <iostream>

int main() {
    double v, T;
    std::cin >> v >> T;
    // const int chill =
    //     static_cast<int>(round(13.12 + 0.6215 * T - 11.37 * pow(v, 0.16) +
    //                            0.3965 * T * pow(v, 0.16) + 0.5));
    const int chill =
        static_cast<int>(floor(13.12 + 0.6215 * T - 11.37 * pow(v, 0.16) +
                               0.3965 * T * pow(v, 0.16) + 0.5));
    printf("%d", chill);
    return 0;
}
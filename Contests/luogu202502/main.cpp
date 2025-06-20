#include <iostream>

const int MAX_N = 2000001;
const int MAX_FACTORS = 10000000; // Estimate based on factor count

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    // Static arrays
    static int last_from[MAX_N] = {0};
    static int change_number[MAX_N] = {0};
    static long long ans[MAX_N];
    static int factors_data[MAX_FACTORS];
    static int factors_start[MAX_N] = {0};
    int factors_size = 0;

    // Initialize
    for (int i = 1; i < MAX_N; ++i) {
        last_from[i] = 1;
        change_number[i] = 1;
    }

    // Precompute factors and last_from
    for (int i = 2; i < MAX_N; ++i) {
        int start = factors_size;
        for (int j = 2 * i; j < MAX_N; j += i) {
            factors_data[factors_size++] = i;
            if (change_number[i] + 1 > change_number[j]) {
                change_number[j] = change_number[i] + 1;
                last_from[j] = i;
            }
        }
        factors_start[i + 1] = factors_size; // Next start
        factors_start[i] = start;
    }

    // // Compute ans
    // ans[1] = 1;
    // for (int i = 2; i < MAX_N; ++i) {
    //     ans[i] = ans[i - 1] + i - 2;
    //
    //     // Add contributions from factors (if any additional contributions needed)
    //     for (int j = factors_start[i]; j < factors_start[i + 1]; ++j) {
    //         int factor = factors_data[j];
    //         // Optionally compute contribution here if needed
    //     }
    //
    //     // Compute contribution directly
    //     long long temp = 0;
    //     int x = i;
    //     while (true) {
    //         if (x < i) {
    //             ans[i]++;
    //         }
    //         if (x == 1) {
    //             temp += 1;
    //             break;
    //         }
    //         int lf = last_from[x];
    //         temp += i / lf - x / lf + 1;
    //         x = lf;
    //     }
    //     ans[i] += temp;
    // }
    //
    // // Queries
    // int t;
    // std::cin >> t;
    // for (int i = 0; i < t; ++i) {
    //     int n;
    //     std::cin >> n;
    //     std::cout << ans[n] << '\n';
    // }
    //
    // return 0;
}
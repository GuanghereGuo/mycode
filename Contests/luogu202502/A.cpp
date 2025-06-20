#include <algorithm>
#include <iostream>
#include <vector>
#include <functional>

const int MAX_N = 2000001;

signed main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    static int last_from[MAX_N];
    static int change_number[MAX_N];
    static long long contribution[MAX_N];
    static std::vector<std::vector<int>> factors(MAX_N);

    std::fill_n(last_from, MAX_N, 1);
    std::fill_n(change_number, MAX_N, 1);

    for (int i = 2; i <= 2e6; i++) {
        for (int j = 2; i * j <= 2e6; j++) {
            factors[i * j].push_back(i);
            if (change_number[i] + 1 > change_number[i * j]) {
                change_number[i * j] = change_number[i] + 1;
                last_from[i * j] = i;
            }
        }
    }

    //std::vector<long long> ans(2e6 + 1);
    static long long ans[MAX_N];
    std::fill_n(ans, MAX_N, 0);
    ans[1] = 1;

    auto get_last = [&](int i, int x) {
        std::vector<int> path;
        while (x > 1) {
            path.push_back(x);
            x = last_from[x];
        }
        if (x == 1) {
            path.push_back(1);
        }

        long long result = 0;
        for (auto it = path.rbegin(); it != path.rend(); ++it) {
            int curr = *it;
            if (curr < i) {
                contribution[curr]++;
            }
            if (curr == 1) {
                result = 1;
            } else {
                int lf = last_from[curr];
                result += i / lf - curr / lf + 1;
            }
        }
        return result;
    };

    for (int i = 2; i <= 2e6; i++) {
        // std::function<long long(int)> get_last = [&](int x) -> long long {
        //     if (x < i) {
        //         contribution[x]++;
        //     }
        //     if (x == 1) {
        //         return 1;
        //     }
        //     // contribution[last_from[i]]++;
        //     return get_last(last_from[x]) + i / last_from[x] - x / last_from[x] + 1;
        // };
        ans[i] = ans[i - 1] + i - 2;
        for (auto j : factors[i]) {
            ans[i] += contribution[j];
        }
        ans[i] += get_last(i, i);
    }

    int t;
    std::cin >> t;

    for (int i = 1; i <= t; i++) {
        int n;
        std::cin >> n;
        std::cout << ans[n] << '\n';
    }
}
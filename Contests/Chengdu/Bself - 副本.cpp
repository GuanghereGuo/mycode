//
// Created by 24087 on 24-11-12.
//
#include <bitset>
#include <iostream>

constexpr int mod = 1e9 + 7;

int main() {
    // std::ios::sync_with_stdio(false);
    // std::cout.tie(nullptr);
    // std::cin.tie(nullptr);

    int n, q;
    std::cin >> n >> q;
    std::string str;
    std::cin >> str;

    std::cerr << str << std::endl;

    int num_a = 0, num_b = 0, num_c = 0;
    for (int i = 0; i < n; i++) {
        if (str[i] == 'a') {
            num_a++;
        } else if (str[i] == 'b') {
            num_b++;
        } else if (str[i] == 'c') {
            num_c++;
        }
    }

    int dp[305][305][305][3] = {0};  // i, a, b, color

    if (str[0] == '?' || str[0] == 'a') {
        dp[1][1][0][0] = 1;
    }
    if (str[0] == '?' || str[0] == 'b') {
        dp[1][0][1][1] = 1;
    }
    if (str[0] == '?' || str[0] == 'c') {
        dp[1][0][0][2] = 1;
    }


    for (int i = 1; i <= q; i++) {
        int a, b, c;
        std::cin >> a >> b >> c;
        std::cout << (dp[n][a + num_a][b + num_b][0] +
                      dp[n][a + num_a][b + num_b][1] +
                      dp[n][a + num_a][b + num_b][2]) %
                         mod
                  << '\n';
    }
    std::cerr << "ojbk" << std::endl;
    return 0;

    for (int i = 2; i <= n; i++) {
        for (int a = 0; a <= i; a++) {
            for (int b = 0; a + b <= i; b++) {
                if (str[i - 1] == '?' || str[i - 1] == 'a') {
                    (dp[i][a][b][0] +=
                     (dp[i - 1][a - 1][b][1] + dp[i - 1][a - 1][b][2]) % mod) %=
                        mod;
                }
                if (str[i - 1] == '?' || str[i - 1] == 'b') {
                    (dp[i][a][b][1] +=
                     (dp[i - 1][a][b - 1][0] + dp[i - 1][a][b - 1][2]) % mod) %=
                        mod;
                }
                if (str[i - 1] == '?' || str[i - 1] == 'c') {
                    (dp[i][a][b][2] +=
                     (dp[i - 1][a][b][0] + dp[i - 1][a][b][1]) % mod) %= mod;
                }
            }
        }
    }
}

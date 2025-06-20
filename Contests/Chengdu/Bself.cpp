//
// Created by 24087 on 24-11-12.
//
#include <iostream>
#include <string>

//#define int unsigned long long

constexpr int mod = 1e9 + 7;

int dp[305][305][305][3] = {0};  // i, a, b, color
int sum[305][305][305] = {0};

signed main() {
    int n, q;
    std::cin >> n >> q;
    std::string str;
    std::cin >> str;

    int num_a = 0, num_b = 0, num_c = 0;
    for (char ch : str) {
        if (ch == 'a') {
            num_a++;
        } else if (ch == 'b') {
            num_b++;
        } else if (ch == 'c') {
            num_c++;
        }
    }

    if (str[0] == '?' || str[0] == 'a') {
        dp[1][1][0][0] = 1;
    }
    if (str[0] == '?' || str[0] == 'b') {
        dp[1][0][1][1] = 1;
    }
    if (str[0] == '?' || str[0] == 'c') {
        dp[1][0][0][2] = 1;
    }

    for (int i = 2; i <= n; i++) {
        for (int a = 0; a <= i; a++) {
            for (int b = 0; a + b <= i; b++) {
                int c = i - a - b;
                if (a > 0 && (str[i - 1] == '?' || str[i - 1] == 'a')) {
                    dp[i][a][b][0] = static_cast<int>((1ll * dp[i][a][b][0] +
                                                      dp[i - 1][a - 1][b][1] +
                                                      dp[i - 1][a - 1][b][2]) %
                                     mod);
                }
                if (b > 0 && (str[i - 1] == '?' || str[i - 1] == 'b')) {
                    dp[i][a][b][1] = static_cast<int>((1ll * dp[i][a][b][1] +
                                                      dp[i - 1][a][b - 1][0] +
                                                      dp[i - 1][a][b - 1][2]) %
                                     mod);
                }
                if (c > 0 && (str[i - 1] == '?' || str[i - 1] == 'c')) {
                    dp[i][a][b][2] = static_cast<int>((1ll * dp[i][a][b][2] +
                                                      dp[i - 1][a][b][0] +
                                                      dp[i - 1][a][b][1]) %
                                     mod);
                }
            }
        }
    }

    for (int i = 1; i <= n + 1; i++) {
        for (int j = 1; j <= n + 1; j++) {
            int k = n + 3 - i - j;
            (sum[i][j][k] +=
             static_cast<int>((1ll * dp[n][i - 1][j - 1][0] +
                              dp[n][i - 1][j - 1][1] + dp[n][i - 1][j - 1][2]) %
             mod)) %= mod;
        }
    }

    for (int i = 1; i <= n + 1; i++) {
        for (int j = 1; j <= n + 1; j++) {
            for (int k = 1; k <= n + 1; k++) {
                (sum[i][j][k] +=
                 static_cast<int>((1ll * sum[i - 1][j][k] + sum[i][j - 1][k] +
                                  sum[i][j][k - 1] - sum[i - 1][j - 1][k] -
                                  sum[i - 1][j][k - 1] - sum[i][j - 1][k - 1] +
                                  sum[i - 1][j - 1][k - 1] + mod * 10ll) %
                 mod)) %= mod;
            }
        }
    }

    for (int i = 0; i < q; i++) {
        int a, b, c;
        std::cin >> a >> b >> c;
        std::cout << sum[std::min(a + num_a, n) + 1][std::min(b + num_b, n) + 1]
                        [std::min(c + num_c, n) + 1]
                  << '\n';
    }
}
/*
* 100 21
?????c??????????????????????????b???a????a?????????????????????????c????????????????????????????????
43 38 20
27 40 32
39 27 33
28 50 43
50 3 46
38 46 14
42 48 10
45 25 28
49 10 49
38 17 42
41 49 22
41 18 44
46 47 25
17 44 35
34 43 22
47 42 32
32 44 40
36 41 24
45 38 45
49 44 18
42 34 32
 */

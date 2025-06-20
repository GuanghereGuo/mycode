#include <bit>
#include <iostream>

using std::cin, std::cout;
int constexpr mod = 998244353;

int f[1000010], n, g[30];

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;

    f[0] = 1;
    for (int i = 1; i <= n; i++) {
        int t = std::bit_width(static_cast<unsigned>(i - 1));
        for (int j = 0; j < t; j++)
            f[i] = (f[i] + f[i - (1 << j) >> j]) % mod;
    }

    g[0] = mod - 1;

    for (int i = 1; i < 20; i++)
        for (int k = 0; k < i; k++)
            g[i] = (g[i] - 1ll * g[k] * f[(1 << (i - k)) - 1] % mod + mod) % mod;
    //g[i] -= g[k] * f[2^(i - k) - 1]

    cout << '\n';
    for (int i = 2; i <= n; i++) {
        int p = std::bit_width((unsigned) i);
        int ans = 0;
        for (int t = 0; t < p; t++)
            if (std::has_single_bit((i >> t) + 1u)) {
                for (int k = t; k < p; k++)
                    ans = (ans + 1ll * g[p - k] * f[i - ((i >> t) << k)] % mod) % mod;
                break;
            }
        cout << ans << ' ';
    }
    return 0;
}

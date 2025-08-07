//
// Created by guanghere on 25-8-7.
//
#include <bits/stdc++.h>


class Generator {
    static constexpr unsigned int U = (1u << 30) - 1;
    std::array<unsigned int, 3> f{};

public:
    Generator(unsigned int a, unsigned int b, unsigned int c) {
        f[0] = a & U;
        f[1] = b & U;
        f[2] = c & U;
    }

    unsigned int next() {
        const unsigned int f_im3 = f[0];
        const unsigned int f_im2 = f[1];
        const unsigned int f_im1 = f[2];

        const unsigned int g = f_im3 ^ ((f_im3 << 16) & U);
        const unsigned int h = g ^ (g >> 5);
        const unsigned int cur_f = h ^ ((h << 1) & U) ^ f_im2 ^ f_im1;

        f[0] = f_im2;
        f[1] = f_im1;
        f[2] = cur_f;

        return cur_f;
    }
};

void solve() {
    int n;
    unsigned int a, b, c;
    std::cin >> n >> a >> b >> c;

    Generator gen(a, b, c);

    bool odd = false;
    std::string ans;
    for (int i = 0; i < n; ++i) {
        if (gen.next() % (n - i) != 0) {
            odd ^= 1;
        }
    }
    if (odd) {
        ans += '1';
    } else {
        ans += '0';
    }
    for (int i = 1; i <= n - 1; i++) {
        int l = gen.next() % n;
        int r = gen.next() % n;
        int d = gen.next() % n + 1;
        if (l > r)
            std::swap(l, r);
        odd ^= (r ^ l) & d & 1;
        if (odd) {
            ans += '1';
        } else {
            ans += '0';
        }
    }
    std::cout << ans << '\n';
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}

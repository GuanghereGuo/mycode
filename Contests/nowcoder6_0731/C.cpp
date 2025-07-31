//
// Created by guanghere on 25-7-31.
//
#include <iostream>
#include <vector>

using namespace std;

const int MOD = 998244353;
const int MAXN = 500005;

long long fact[MAXN];
long long s1[MAXN], s2[MAXN], s3[MAXN];

void precompute() {
    fact[0] = 1;
    fact[1] = 1;
    s1[1] = 1;
    s2[1] = 1;
    s3[1] = 1;

    for (int i = 2; i < MAXN; ++i) {
        long long i_ll = i;
        fact[i] = (fact[i - 1] * i_ll) % MOD;

        s1[i] = (i_ll * s1[i - 1] + fact[i - 1]) % MOD;

        long long term_s2 = (2 * s1[i - 1] + fact[i - 1]) % MOD;
        s2[i] = (i_ll * s2[i - 1] + term_s2) % MOD;

        long long term_s3_1 = (3 * s2[i - 1]) % MOD;
        long long term_s3_2 = (3 * s1[i - 1]) % MOD;
        long long term_s3 = (term_s3_1 + term_s3_2 + fact[i - 1]) % MOD;
        s3[i] = (i_ll * s3[i - 1] + term_s3) % MOD;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    precompute();

    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        cout << s3[n] << "\n";
    }

    return 0;
}
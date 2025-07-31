//
// Created by guanghere on 25-7-31.
//
//
// Created by guanghere on 25-7-31.
//
#include <iostream>
#include <vector>

using namespace std;
using ll = long long;

const int N_MAX = 5005;
const int MOD = 998244353;

int n;
vector<int> g[N_MAX];
int sz[N_MAX];
vector<ll> dp[N_MAX][2];

ll fact[N_MAX];
ll invf[N_MAX];

ll power(ll base, ll exp) {
    ll res = 1;
    base %= MOD;
    while (exp > 0) {
        if (exp % 2 == 1) res = (res * base) % MOD;
        base = (base * base) % MOD;
        exp /= 2;
    }
    return res;
}

ll inverse(ll num) {
    return power(num, MOD - 2);
}

void precompute_combi(int max_n) {
    fact[0] = 1;
    invf[0] = 1;
    for (int i = 1; i <= max_n; ++i) {
        fact[i] = (fact[i - 1] * i) % MOD;
        invf[i] = inverse(fact[i]);
    }
}

ll combinations(int n_items, int k_items) {
    if (k_items < 0 || k_items > n_items) {
        return 0;
    }
    return (((fact[n_items] * invf[k_items]) % MOD) * invf[n_items - k_items]) % MOD;
}

void dfs(int u, int p) {
    sz[u] = 1;
    dp[u][0] = {1}; // Not choosing u: {1} -> 1*x^0
    dp[u][1] = {0, 1}; // Choosing u: {0, 1} -> 1*x^1

    for (int v : g[u]) {
        if (v == p) continue;
        dfs(v, u);

        vector<ll> next_dp0(sz[u] + sz[v], 0);
        vector<ll> next_dp1(sz[u] + sz[v], 0);

        vector<ll> v_sum(sz[v] + 1, 0);
        for (int i = 0; i < dp[v][0].size(); ++i) v_sum[i] = (v_sum[i] + dp[v][0][i]) % MOD;
        for (int i = 0; i < dp[v][1].size(); ++i) v_sum[i] = (v_sum[i] + dp[v][1][i]) % MOD;

        // Convolution for dp[u][0]
        for (int i = 0; i < dp[u][0].size(); ++i) {
            for (int j = 0; j < v_sum.size(); ++j) {
                if (i + j < next_dp0.size()) {
                    next_dp0[i + j] = (next_dp0[i + j] + dp[u][0][i] * v_sum[j]) % MOD;
                }
            }
        }

        // Convolution for dp[u][1]
        for (int i = 0; i < dp[u][1].size(); ++i) {
            for (int j = 0; j < dp[v][0].size(); ++j) {
                 if (i + j < next_dp1.size()) {
                    next_dp1[i + j] = (next_dp1[i + j] + dp[u][1][i] * dp[v][0][j]) % MOD;
                }
            }
        }

        sz[u] += sz[v];
        dp[u][0] = next_dp0;
        dp[u][1] = next_dp1;
    }
}

void solve() {
    cin >> n;
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    precompute_combi(n);
    dfs(1, 0);

    vector<ll> I(n + 1, 0);
    for (int i = 0; i < dp[1][0].size(); ++i) I[i] = (I[i] + dp[1][0][i]) % MOD;
    for (int i = 0; i < dp[1][1].size(); ++i) I[i] = (I[i] + dp[1][1][i]) % MOD;

    ll expected_rounds = 0;
    for (int j = 1; j <= n; ++j) {
        ll c_nj = combinations(n, j);
        if (c_nj == 0) continue; // Should not happen for j in [1, n]

        ll term = (I[j] * inverse(c_nj)) % MOD;
        expected_rounds = (expected_rounds + 1 - term + MOD) % MOD;
    }

    cout << expected_rounds << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}

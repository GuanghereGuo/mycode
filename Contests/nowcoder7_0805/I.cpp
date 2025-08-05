//Author: Alencryenfo
//Date: 2025-08-05 08:31:18
#include <iostream>
#include <vector>
using namespace std;

using ll = long long;
using ull = unsigned long long;

const int MOD = 998244353;

ll qpow(ll a, unsigned long long e = MOD - 2)
{
    ll r = 1;
    for (; e; e >>= 1, a = a * a % MOD)
        if (e & 1) r = r * a % MOD;
    return r;
}

struct Mat
{
    ll a[18][18]{};

    Mat(bool id = false)
    {
        if (id) for (int i = 0; i < 18; ++i) a[i][i] = 1;
    }

    Mat operator*(const Mat& o) const
    {
        Mat r;
        for (int i = 0; i < 18; ++i)
            for (int k = 0; k < 18; ++k)
                if (a[i][k])
                    for (int j = 0; j < 18; ++j)
                        r.a[i][j] = (r.a[i][j] + a[i][k] * o.a[k][j]) % MOD;
        return r;
    }
};

Mat mpow(Mat base, unsigned long long e)
{
    Mat r(true);
    while (e)
    {
        if (e & 1) r = base * r;
        base = base * base;
        e >>= 1;
    }
    return r;
}

signed main()
{
#ifdef DEBUG
    freopen("test.in", "r", stdin);
    freopen("test.out", "w", stdout);
#endif
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int T;
    cin >> T;
    while (T--)
    {
        ll n;
        int k;
        cin >> n >> k;
        vector<int> D(k);
        for (int& d : D) cin >> d;
        ll inv5 = qpow(5), invk = qpow(k);
        ll mu = 0;
        for (int d : D) mu = (mu + d) % MOD;
        mu = mu * invk % MOD;
        ll alpha = (mu + 3) % MOD * inv5 % MOD;
        ll gamma = 3 * mu % MOD * inv5 % MOD;
        ll delta = 2 * inv5 % MOD;
        ll w[16]{};
        for (int r = 0; r < 16; ++r)
        {
            for (int d : D) w[r] = (w[r] + (r & d)) % MOD;
            w[r] = w[r] * invk % MOD;
        }
        ll P[16][16]{};
        const char ops[5]{'+', '*', '&', '|', '^'};
        ll invAll = qpow(5LL * k % MOD);
        auto nxt = [](int s, char op, int d)
        {
            switch (op)
            {
            case '+': return (s + d) & 15;
            case '*': return (s * d) & 15;
            case '&': return s & d;
            case '|': return s | d;
            default: return s ^ d;
            }
        };
        for (int s = 0; s < 16; ++s)
            for (char op : ops)
                for (int d : D)
                {
                    int r = nxt(s, op, d);
                    P[r][s] = (P[r][s] + invAll) % MOD;
                }
        Mat A;
        A.a[0][0] = 1;
        A.a[1][0] = gamma;
        A.a[1][1] = alpha;
        for (int r = 0; r < 16; ++r)
            A.a[1][2 + r] = (MOD - delta) * w[r] % MOD;
        for (int r = 0; r < 16; ++r)
            for (int s = 0; s < 16; ++s)
                A.a[2 + r][2 + s] = P[r][s];
        ll v[18]{1, mu};
        for (int d : D) v[2 + (d & 15)] = (v[2 + (d & 15)] + invk) % MOD;
        if (n == 1)
        {
            cout << mu << '\n';
            continue;
        }
        Mat An = mpow(A, n - 1);
        ll ans = 0;
        for (int j = 0; j < 18; ++j)
            ans = (ans + An.a[1][j] * v[j]) % MOD;
        cout << ans << '\n';
    }
    return 0;
}

/*
{
"C++版本":"C++23",
"优化等级":"-O2",
"时间限制":5000,
"内存限制":1024,
"自动测试":1,
}
<<7
3
1 1
5
2 2
1 2
10000 9
1 2 3 4 5 6 7 8 9
>>3
5
848507702
463950893
*/

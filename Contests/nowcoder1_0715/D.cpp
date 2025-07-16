#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int SMALL = 1000000; // 小质数范围，略大于 sqrt(10^10) ≈ 10^5
vector<int> primes;        // 存储小于等于 SMALL 的质数

// 埃拉托斯特尼筛法，预处理小质数
void sieve() {
    vector<bool> is_prime(SMALL + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i <= SMALL; i++) {
        if (is_prime[i]) {
            primes.push_back(i);
            for (ll j = (ll)i * i; j <= SMALL; j += i) {
                is_prime[j] = false;
            }
        }
    }
}

// 快速幂计算 a^b mod p
ll mod_pow(ll a, ll b, ll mod) {
    ll res = 1;
    ll base = a % mod;
    while (b > 0) {
        if (b & 1) res = (__int128)res * base % mod;
        base = (__int128)base * base % mod;
        b >>= 1;
    }
    return res;
}

// Min_25 筛法相关变量
vector<ll> num;  // 存储 n/i 的不同值
vector<int> id1, id2; // 离散化数组，id1 为 <= sqrt(n)，id2 为 > sqrt(n)
int cnt;         // num 数组大小
ll n, p;         // 全局变量 n 和 p

// 预处理 num, id1, id2 数组
void precompute() {
    ll sqr = (ll)sqrt(n) + 1;
    cnt = 0;
    for (ll i = 1; i <= n; i = n / (n / i) + 1) {
        num.push_back(n / i);
        if (num.back() <= sqr) id1.push_back(cnt);
        else id2.push_back(cnt);
        cnt++;
    }
}

// Min_25 筛法的 S 函数
// S(x, j) 表示 [2, x] 中最小质因子 >= primes[j] 的数的函数值之和
ll S(ll x, int j) {
    if (x <= 1 || j >= (int)primes.size() || primes[j] > x) return 0;
    ll res = 0;
    for (int k = j; k < (int)primes.size() && (ll)primes[k] * primes[k] <= x; k++) {
        ll pk = primes[k];
        ll pk_e = pk;
        int e = 1;
        while (pk_e * pk <= x) {
            res = (res + S(x / pk_e, k + 1) * mod_pow(pk, e, p)) % p;
            res = (res + mod_pow(pk, e, p)) % p; // 单独项 p^e
            pk_e *= pk;
            e++;
        }
    }
    return res;
}

// Min_25 筛法计算大质数乘积
ll min_25() {
    precompute();

    // g(n, j) 表示 [1, n] 中最小质因子 > primes[j] 的数的函数值之和
    vector<ll> g(cnt, 0);
    // 初始值：假设所有数都是质数，f(n) = n
    for (int i = 0; i < cnt; i++) {
        g[i] = num[i] % p;
    }

    // 递推计算 g 数组
    for (int i = 0; i < (int)primes.size(); i++) {
        ll pr = primes[i];
        if (pr * pr > n) break;
        for (int j = 0; j < cnt && pr * pr <= num[j]; j++) {
            ll d = num[j] / pr;
            int k = (d <= (ll)sqrt(n)) ? id1[d] : id2[n / d];
            g[j] = (g[j] - (g[k] - (i > 0 ? g[id1[primes[i - 1]]] : 0)) % p + p) % p;
        }
    }

    // 计算 S(n, j)，从第一个大于 SMALL 的质数开始
    int j = 0;
    while (j < (int)primes.size() && primes[j] <= SMALL) j++;
    ll ans = S(n, j);
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> p;

    if (n == 1) {
        cout << 1 << "\n";
        return 0;
    }

    sieve();

    ll ans = 1;

    // 处理小质数的贡献
    for (int pr : primes) {
        if ((ll)pr > n) break;
        ll exp = 1;
        ll power = pr;
        while (n / pr >= power) {
            power *= pr;
            exp++;
        }
        ans = (__int128)ans * mod_pow(pr, exp, p) % p;
    }

    // 处理大质数的贡献（> SMALL 且 <= n，指数为 1）
    if (n > SMALL) {
        ll big_primes_contribution = min_25();
        ans = (__int128)ans * big_primes_contribution % p;
    }

    cout << ans << "\n";
    return 0;
}

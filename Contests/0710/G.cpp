// //
// // Created by guanghere on 25-7-10.
// //
// #include <bits/stdc++.h>
// using namespace std;
//
// int main() {
//     ios::sync_with_stdio(false);
//     cin.tie(nullptr);
//     int n;
//     cin >> n;
//     vector<int> w(n), c(n);
//     for (auto& x : w) cin >> x;
//     for (auto& x : c) cin >> x;
//     const int MAXW = 500005;
//     vector<int> spf(MAXW);
//     for (int i = 0; i < MAXW; i++) spf[i] = i;
//     for (long long i = 2; i < MAXW; i++) {
//         if (spf[i] == i) {
//             for (long long j = i * i; j < MAXW; j += i) {
//                 if (spf[j] == j) spf[j] = i;
//             }
//         }
//     }
//     auto get_primes = [&](int x) -> vector<int> {
//         vector<int> res;
//         if (x <= 1) return res;
//         while (x > 1) {
//             int p = spf[x];
//             res.push_back(p);
//             while (x % p == 0) x /= p;
//         }
//         return res;
//     };
//     struct Group {
//         map<int, int> color_max;
//         multiset<int> vals;
//     };
//     map<int, Group> prime_groups;
//     int ans = 0;
//     for (int i = 0; i < n; i++) {
//         vector<int> primes = get_primes(w[i]);
//         int max_prev = 0;
//         for (int p : primes) {
//             auto it = prime_groups.find(p);
//             if (it == prime_groups.end()) continue;
//             auto& g = it->second;
//             int temp = 0;
//             bool has = g.color_max.count(c[i]);
//             if (has) {
//                 int v = g.color_max[c[i]];
//                 auto sit = g.vals.find(v);
//                 if (sit != g.vals.end()) {
//                     g.vals.erase(sit);
//                     temp = g.vals.empty() ? 0 : *g.vals.rbegin();
//                     g.vals.insert(v);
//                 } else {
//                     temp = g.vals.empty() ? 0 : *g.vals.rbegin();
//                 }
//             } else {
//                 temp = g.vals.empty() ? 0 : *g.vals.rbegin();
//             }
//             max_prev = max(max_prev, temp);
//         }
//         int dpi = 1 + max_prev;
//         ans = max(ans, dpi);
//
//         for (int p : primes) {
//             auto& g = prime_groups[p];
//             int cc = c[i];
//             int old_v = g.color_max.count(cc) ? g.color_max[cc] : 0;
//             int new_v = max(old_v, dpi);
//             if (old_v > 0) {
//                 auto sit = g.vals.find(old_v);
//                 if (sit != g.vals.end()) {
//                     g.vals.erase(sit);
//                 }
//             }
//             g.color_max[cc] = new_v;
//             g.vals.insert(new_v);
//         }
//     }
//     cout << ans << endl;
//     return 0;
// }
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXA = 500000;

struct Rec {
    int len = 0;
    int col = -1;
};

inline void insert_rec(Rec &a, Rec &b, int len, int col) {
    if (col == a.col) {
        if (len > a.len) a.len = len;
    } else {
        if (len > a.len) {
            b = a;
            a = {len, col};
        } else if (col == b.col) {
            if (len > b.len) b.len = len;
        } else if (len > b.len) {
            b = {len, col};
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    static int spf[MAXA + 1];
    vector<int> primes;
    for (int i = 2; i <= MAXA; ++i) {
        if (!spf[i]) { spf[i] = i; primes.push_back(i); }
        for (int p : primes) {
            if (p > spf[i] || 1LL * p * i > MAXA) break;
            spf[p * i] = p;
        }
    }

    int n;
    cin >> n;
    vector<int> w(n), c(n);
    for (int &x : w) cin >> x;
    for (int &x : c) cin >> x;

    static Rec best1[MAXA + 1], best2[MAXA + 1];

    int ans = 1;
    vector<int> fac;
    fac.reserve(10);

    for (int i = 0; i < n; ++i) {
        int x = w[i];
        fac.clear();
        while (x > 1) {
            int p = spf[x];
            fac.push_back(p);
            while (x % p == 0) x /= p;
        }
        if (fac.empty()) {
            ans = max(ans, 1);
            continue;
        }

        int mx = 0;
        for (int p : fac) {
            if (best1[p].col != c[i])
                mx = max(mx, best1[p].len);
            else
                mx = max(mx, best2[p].len);
        }

        int cur = mx + 1;
        ans = max(ans, cur);

        for (int p : fac)
            insert_rec(best1[p], best2[p], cur, c[i]);
    }

    cout << ans << '\n';
    return 0;
}


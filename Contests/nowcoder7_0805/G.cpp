//
// Created by guanghere on 25-8-5.
//
#include <bits/stdc++.h>

using ll = long long;

const int N = 1'000'000;
std::vector<int> p;
bool is_p[N + 1];
std::vector<ll> ans;
ll n;

void sieve() {
    std::fill(is_p, is_p + N + 1, true);
    is_p[0] = is_p[1] = false;
    for (int i = 2; i * i <= N; ++i) {
        if (is_p[i]) {
            for (int j = i * i; j <= N; j += i) {
                is_p[j] = false;
            }
        }
    }
    for (int i = 2; i <= N; ++i) {
        if (is_p[i]) {
            p.push_back(i);
        }
    }
}

void dfs(int idx, ll now, int cnt) {
    if (cnt > 0 && (cnt % 2 != 0)) {
        ans.push_back(now);
    }
    if (ans.size() >= n / 2) {
        return;
    }
    for (auto i = idx; i < p.size(); ++i) {
        if (now > n / p[i]) {
            break;
        }
        ll nxt = now * p[i];
        dfs(i, nxt, cnt + 1);
        if (ans.size() >= n / 2) {
            return;
        }
    }
}

void solve() {
    std::cin >> n;
    ans.clear();

    dfs(0, 1, 0);

    for (int i = 0; i < n / 2; ++i) {
        std::cout << ans[i] << (i == n / 2 - 1 ? "" : " ");
    }
    std::cout << "\n";
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    sieve();
    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}

//
// Created by guanghere on 25-7-12.
//
#include <bits/stdc++.h>
using namespace std;

const int N = 200010;
vector<int> adj[N];
bool tag[N];
int tag_cnt;
long long E;
int dist_n;
int n;

int dfs(int u, int fa, int dep) {
    int cnt = tag[u] ? 1 : 0;
    for (int v : adj[u]) {
        if (v != fa) {
            int child_cnt = dfs(v, u, dep + 1);
            if (child_cnt != 0) {
                E += 1;
            }
            cnt += child_cnt;
        }
    }
    if (u == n - 1) {
        dist_n = dep;
    }
    return cnt;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    string s;
    cin >> s;

    for (int i = 0; i < n; i++) {
        tag[i] = (s[i] == '1' || i == 0 || i == n - 1);
        if (tag[i]) tag_cnt++;
    }

    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    E = 0;
    dfs(0, -1, 0);
    cout << 2LL * E - dist_n << "\n";

    return 0;
}
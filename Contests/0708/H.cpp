#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using tiii = tuple<int, int, int>;

const int dx[] = {0, 0, 1, 1, 1, -1, -1, -1};
const int dy[] = {1, -1, 0, 1, -1, 0, 1, -1};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        int l, r;
        cin >> l >> r;
        vector<string> grid(n);
        for (int i = 0; i < n; ++i) {
            cin >> grid[i];
        }

        vector vis(2, vector(n, vector<int>(m, -1)));
        queue<tiii> q;
        q.emplace(0, 0, 0); // (x, y, c)
        vis[0][0][0] = 0;

        while (!q.empty()) {
            auto [x, y, c] = q.front();
            q.pop();
            int nc = 1 - c;
            for (int i = 0; i < 8; ++i) {
                int nx = x + dx[i];
                int ny = y + dy[i];
                if (nx >= 0 && nx < n && ny >= 0 && ny < m && grid[nx][ny] == '1' && vis[nc][nx][ny] == -1) {
                    vis[nc][nx][ny] = vis[c][x][y] + 1;
                    q.emplace(nx, ny, nc);
                }
            }
        }

        int d_even = vis[0][n-1][m-1];
        int d_odd = vis[1][n-1][m-1];
        int v;
        if (d_even != -1 && d_odd != -1) {
            v = min(d_even, d_odd);
        } else if (d_even != -1) {
            v = d_even;
        } else if (d_odd != -1) {
            v = d_odd;
        } else {
            cout << -1 << '\n';
            continue;
        }

        if (l != r) {
            cout << (v + r - 1) / r << '\n';
        } else {
            if (r % 2 == 0) {
                if (d_even == -1) {
                    cout << -1 << '\n';
                } else {
                    cout << (d_even + r - 1) / r << '\n';
                }
            } else {
                int k = 1e9;
                if (d_odd != -1) {
                    k = min(k, (d_odd + r - 1) / r);
                    if (k % 2 == 0) {
                        k++;
                    }
                    //std::cerr << k << '\n';
                }
                if (d_even != -1) {
                    int kk = (d_even + r - 1) / r;
                    k = min(k, kk + (kk & 1));
                }
                std::cout << k << '\n';
            }
        }
    }
}
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 3e6 + 5, K = 5e5;
int n, m, s, opt, x, y, z, l, r, w, a[N], cnt, hd[N], to[N], nxt[N], val[N],
    d[N];
bool v[N];
priority_queue<pair<int, int> > q;
void add(int x, int y, int z) {
    to[++cnt] = y, nxt[cnt] = hd[x], hd[x] = cnt, val[cnt] = z;
}
void build(int p, int l, int r) {
    if (l == r) {
        a[l] = p;
        return;
    }
    int mid = (l + r) / 2;
    add(p, p << 1, 0), add(p, p << 1 | 1, 0);
    add((p << 1) + K, p + K, 0), add((p << 1 | 1) + K, p + K, 0);
    build(p << 1, l, mid);
    build(p << 1 | 1, mid + 1, r);
}
void modify(int p, int l, int r, int lx, int rx, int v, int w) {
    if (l >= lx && r <= rx) {
        if (opt == 2)
            add(v + K, p, w);
        else
            add(p + K, v, w);
        return;
    }
    int mid = (l + r) / 2;
    if (lx <= mid) modify(p << 1, l, mid, lx, rx, v, w);
    if (rx > mid) modify(p << 1 | 1, mid + 1, r, lx, rx, v, w);
}
void dij(int s) {
    memset(d, 0x3f, sizeof(d)), d[s] = 0;
    q.push(make_pair(0, s));
    while (q.size()) {
        int x = q.top().second;
        q.pop();
        if (v[x]) continue;
        v[x] = 1;
        for (int i = hd[x]; i; i = nxt[i]) {
            int y = to[i], z = val[i];
            if (d[y] > d[x] + z) d[y] = d[x] + z, q.push(make_pair(-d[y], y));
        }
    }
}
signed main() {
    scanf("%lld%lld%lld", &n, &m, &s), build(1, 1, n);
    for (int i = 1; i <= n; i++) add(a[i], a[i] + K, 0), add(a[i] + K, a[i], 0);
    for (int i = 1; i <= m; i++) {
        scanf("%lld", &opt);
        if (opt == 1)
            scanf("%lld%lld%lld", &x, &y, &z), add(a[x] + K, a[y], z);
        else {
            scanf("%lld%lld%lld%lld", &x, &l, &r, &w);
            modify(1, 1, n, l, r, a[x], w);
        }
    }
    dij(a[s] + K);
    for (int i = 1; i <= n; i++)
        printf("%lld%c", d[a[i]] != 0x3f3f3f3f3f3f3f3fll ? d[a[i]] : -1,
               i == n ? '\n' : ' ');
    return 0;
}
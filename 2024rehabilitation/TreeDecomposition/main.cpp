#include <iostream>
#include <vector>
using ll = long long;

class BIT {
    std::vector<ll> tr;
    int n, mod;

    static int low_bit(int x) { return x & -x; }

public:
    BIT(int size, int mod) : n(size), mod(mod), tr(size + 1) {}

    void add(int idx, ll val) {
        val = (val % mod + mod) % mod;  // 确保 val 为非负数
        for (int i = idx; i <= n; i += low_bit(i)) {
            tr[i] += val;
            tr[i] %= mod;
        }
    }

    ll query(int idx) {
        ll res = 0;
        for (int i = idx; i; i -= low_bit(i)) {
            res += tr[i];
            res %= mod;
        }
        return res;
    }
};

class EBIT {
    BIT d, di;
    int n, mod;

public:
    EBIT(int size, int mod) : n(size), mod(mod), d(size, mod), di(size, mod) {}

    void add(int l, int r, int val) {
        if (l > r) std::swap(l, r);
        d.add(l, val);
        if (r + 1 <= n) d.add(r + 1, -val);
        di.add(l, val * l);
        if (r + 1 <= n) di.add(r + 1, -val * (r + 1));
    }

    ll query(int l, int r) {
        if (l > r) std::swap(l, r);
        if (l == 1) return query(r);  // 避免访问 query(0)
        return (mod + query(r) - query(l - 1)) % mod;
    }

    ll query(int x) {
        return (x + 1) * d.query(x) % mod - di.query(x) % mod;
    }
};

class TreeDecomposition {
    struct Node {
        int fa = 0, siz = 1, dep = 0, son = 0, top = 0, dfn = 0;
    };

    int n, s, mod, tot;  // 新增成员变量 tot
    std::vector<std::vector<int>> tr;
    std::vector<Node> nodes;
    EBIT bit;

    void dfs1(int now, int father, int depth) {
        nodes[now].fa = father;
        nodes[now].dep = depth;
        for (int nxt : tr[now]) {
            if (nxt == father) continue;
            dfs1(nxt, now, depth + 1);
            nodes[now].siz += nodes[nxt].siz;
            if (nodes[nxt].siz > nodes[nodes[now].son].siz) {
                nodes[now].son = nxt;
            }
        }
    }

    void dfs2(int now, int tp) {
        nodes[now].top = tp;
        nodes[now].dfn = ++tot;
        if (nodes[now].son == 0) return;
        dfs2(nodes[now].son, tp);
        for (int nxt : tr[now]) {
            if (nxt == nodes[now].son || nxt == nodes[now].fa) continue;
            dfs2(nxt, nxt);
        }
    }

public:
    TreeDecomposition(int n, int s, int mod, std::vector<std::vector<int>> &&tr, std::vector<int> &&val)
        : n(n), s(s), mod(mod), tr(std::move(tr)), nodes(n + 1), bit(n, mod), tot(0) {
        nodes[0].siz = 0;
        dfs1(s, 0, 1);
        dfs2(s, s);
        for (int i = 1; i <= n; i++) {
            bit.add(nodes[i].dfn, nodes[i].dfn, val[i]);
        }
    }

    void modify_lca(int u, int v, int val) {
        while (nodes[u].top != nodes[v].top) {
            if (nodes[nodes[u].top].dep > nodes[nodes[v].top].dep) {
                bit.add(nodes[nodes[u].top].dfn, nodes[u].dfn, val);
                u = nodes[nodes[u].top].fa;
            } else {
                bit.add(nodes[nodes[v].top].dfn, nodes[v].dfn, val);
                v = nodes[nodes[v].top].fa;
            }
        }
        bit.add(nodes[u].dfn, nodes[v].dfn, val);
    }

    void modify_subtree(int u, int val) {
        bit.add(nodes[u].dfn, nodes[u].dfn + nodes[u].siz - 1, val);
    }

    ll query_lca(int u, int v) {
        ll res = 0;
        while (nodes[u].top != nodes[v].top) {
            if (nodes[nodes[u].top].dep > nodes[nodes[v].top].dep) {
                res += bit.query(nodes[nodes[u].top].dfn, nodes[u].dfn);
                res %= mod;
                u = nodes[nodes[u].top].fa;
            } else {
                res += bit.query(nodes[nodes[v].top].dfn, nodes[v].dfn);
                res %= mod;
                v = nodes[nodes[v].top].fa;
            }
        }
        res += bit.query(nodes[u].dfn, nodes[v].dfn);
        res %= mod;
        return res;
    }

    ll query_subtree(int u) {
        return bit.query(nodes[u].dfn, nodes[u].dfn + nodes[u].siz - 1);
    }
};

int main() {
    int n, m, s, p;
    std::cin >> n >> m >> s >> p;
    std::vector<std::vector<int>> tr(n + 1);
    std::vector<int> val(n + 1);

    for (int i = 1; i <= n; i++) {
        std::cin >> val[i];
    }

    for (int i = 1, u, v; i <= n - 1; i++) {
        std::cin >> u >> v;
        tr[u].push_back(v);
        tr[v].push_back(u);
    }

    TreeDecomposition td(n, s, p, std::move(tr), std::move(val));

    for (int i = 1, x, y, z, _lca; i <= m; i++) {
        char opt;
        std::cin >> opt;
        switch (opt) {
            case '1':
                std::cin >> x >> y >> z;
                td.modify_lca(x, y, z);
                break;
            case '2':
                std::cin >> x >> y;
                std::cout << td.query_lca(x, y) << '\n';
                break;
            case '3':
                std::cin >> x >> z;
                td.modify_subtree(x, z);
                break;
            case '4':
                std::cin >> x;
                std::cout << td.query_subtree(x) << '\n';
                break;
            default:
                std::cerr << "ERR\n";
                break;
        }
    }
}

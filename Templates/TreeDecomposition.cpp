#include <functional>
#include <iostream>
#include <vector>
using ll = long long;

template<class T>
class Segment_tree {
#define out_of_range() (r < tar_l || l > tar_r)
#define in_range() (tar_l <= l && r <= tar_r)
    struct node {
        T sum = 0;
        T add_lzy = 0;
    };
    //node_val == origin_val * mul_lzy + add_lzy
    int n, mod;
    std::vector<node> data;

    void pull_up(unsigned idx) {
        data[idx].sum = (data[idx << 1].sum + data[idx << 1 | 1].sum) % mod;
    }

    void make_add(unsigned idx, unsigned l, unsigned r, T val) {
        (data[idx].sum += val * (r - l + 1)) %= mod;
        (data[idx].add_lzy += val) %= mod;
    }

    void push_down(unsigned idx, unsigned l, unsigned r) {
        auto mid = l + (r - l) / 2;
        make_add(idx << 1, l, mid, data[idx].add_lzy);
        make_add(idx << 1 | 1, mid + 1, r, data[idx].add_lzy);
        data[idx].add_lzy = 0;
    }

    T ask(unsigned idx, unsigned l, unsigned r, unsigned tar_l, unsigned tar_r) {
        if(out_of_range()) {
            return 0;
        }
        if(in_range()) {
            return data[idx].sum;
        }
        push_down(idx, l, r);
        auto mid = l + (r - l) / 2;
        return (ask(idx << 1, l, mid, tar_l, tar_r) + ask(idx << 1 | 1, mid + 1, r, tar_l, tar_r)) % mod;
    }

    void add(unsigned idx, unsigned l, unsigned r, unsigned tar_l, unsigned tar_r, T val) {
        if(out_of_range()) {
            return;
        }
        if(in_range()) {
            make_add(idx, l, r, val);
            return;
        }
        auto mid = l + (r - l) / 2;
        push_down(idx, l, r);
        add(idx << 1, l, mid, tar_l, tar_r, val);
        add(idx << 1 | 1, mid + 1, r, tar_l, tar_r, val);
        pull_up(idx);
    }
public:

    explicit Segment_tree(const int n, const int &p = 571373) noexcept : n(n), mod(p),
        data(n * 4 + 5) {
    }
    T ask(unsigned l, unsigned r) {
        if(l > r)
            std::swap(l, r);
        return ask(1, 1, n, l, r);
    }
    void add(unsigned l, unsigned r, T val) {
        if(l > r)
            std::swap(l, r);
        add(1, 1, n, l, r, val);
    }
#undef out_of_range
#undef in_range
};

class TreeDecomposition {
    struct Node {
        int fa = 0, siz = 1, dep = 0, son = 0, top = 0, dfn = 0;
    };

    int n, s, mod;
    std::vector<std::vector<int>> tr;
    std::vector<Node> nodes;
    Segment_tree<ll> bit;

    void dfs1(int now, int father, int depth) {
        nodes[now].fa = father;
        nodes[now].dep = depth;
        for (int nxt : tr[now]) {
            if (nxt == father) {
                continue;
            }
            dfs1(nxt, now, depth + 1);
            nodes[now].siz += nodes[nxt].siz;
            if (nodes[nxt].siz >
                nodes[nodes[now].son].siz) {  // 要保证nodes[0].siz = 0
                nodes[now].son = nxt;
            }
        }
    }

    void dfs2(int now, int tp) {
        static int tot = 0;
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
    TreeDecomposition(int n, int s, int mod, std::vector<std::vector<int>> &&tr,
                      std::vector<int> &&val)
        : n(n), s(s), mod(mod), tr(std::move(tr)), nodes(n + 1), bit(n, mod) {
        nodes[0].siz = 0;  //!!!!!!!
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
                res += bit.ask(nodes[nodes[u].top].dfn, nodes[u].dfn);
                res %= mod;
                u = nodes[nodes[u].top].fa;
            } else {
                res += bit.ask(nodes[nodes[v].top].dfn, nodes[v].dfn);
                res %= mod;
                v = nodes[nodes[v].top].fa;
            }
        }
        res += bit.ask(nodes[u].dfn, nodes[v].dfn);
        res %= mod;
        return res;
    }
    ll query_subtree(int u) {
        return bit.ask(nodes[u].dfn, nodes[u].dfn + nodes[u].siz - 1);
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
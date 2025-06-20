#include <iostream>
#include <vector>

class TreeDecomposition {
    struct Node {
        int fa = 0, siz = 1, dep = 0, son = 0, top = 0, dfn = 0;
    };

    int n, s;
    std::vector<std::vector<int>> tr;
    std::vector<Node> nodes;

    void dfs1(int now, int father, int depth) {
        nodes[now].fa = father;
        nodes[now].dep = depth;
        for (int nxt : tr[now]) {
            if (nxt == father) {
                continue;
            }
            dfs1(nxt, now, depth + 1);
            nodes[now].siz += nodes[nxt].siz;
            if (nodes[nxt].siz > nodes[nodes[now].son].siz) {//要保证nodes[0].siz = 0
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
    TreeDecomposition(int n, int s, std::vector<std::vector<int>> &&tr)
        : n(n), s(s), tr(std::move(tr)), nodes(n + 1) {
        nodes[0].siz = 0;
        dfs1(s, 0, 1);
        dfs2(s, s);
    }

    int operator()(int u, int v) {
        while (nodes[u].top != nodes[v].top) {
            if (nodes[nodes[u].top].dep > nodes[nodes[v].top].dep) {
                u = nodes[nodes[u].top].fa;
            } else {
                v = nodes[nodes[v].top].fa;
            }
        }
        return nodes[u].dep < nodes[v].dep ? u : v;
    }
};

int main() {
    int n, m, s;
    std::cin >> n >> m >> s;
    std::vector<std::vector<int>> tr(n + 1);

    for (int i = 1, u, v; i <= n - 1; i++) {
        std::cin >> u >> v;
        tr[u].push_back(v);
        tr[v].push_back(u);
    }

    TreeDecomposition lca(n, s, std::move(tr));

    for (int i = 1, u, v; i <= m; i++) {
        std::cin >> u >> v;
        std::cout << lca(u, v) << '\n';
    }
}

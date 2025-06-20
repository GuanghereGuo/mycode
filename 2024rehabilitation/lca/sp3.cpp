//
// Created by 24087 on 24-9-30.
//
#include <iostream>
#include <vector>

std::vector<std::vector<int>> tr;
std::vector<int> father, siz, son, depth, top, dfn = {0};

void init1(int now, int dep, int fa) {
    father[now] = fa;
    depth[now] =  dep;
    siz[now] = 1;
    son[now] = -1;
    for (const auto nxt : tr[now]) {
        if(depth[nxt]) {
            continue;
        }
        init1(nxt, dep + 1, now);
        siz[now] += siz[nxt];
        if(son[now] == -1 || siz[son[now]] < siz[nxt]) {
            son[now] = nxt;
        }
    }
}

void init2(int now, int tp) {
    top[now] = tp;
    dfn.push_back(dfn.back() + 1);
    if(son[now] == -1) {
        return;
    }
    init2(son[now], tp);
    for(int i : tr[now]) {
        if(i == son[now] || i == father[now]) {
            continue;
        }
        init2(i, i);
    }
}

int lca(int u, int v) {
    while (top[u] != top[v]) {
        if (depth[top[u]] > depth[top[v]])
            u = father[top[u]];
        else
            v = father[top[v]];
    }
    return depth[u] > depth[v] ? v : u;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, m, root;
    std::cin >> n >> m >> root;

    tr.resize(n + 1);
    father.resize(n + 1);
    siz.resize(n + 1);
    son.resize(n + 1);
    depth.resize(n + 1);
    top.resize(n + 1);

    for (int i = 1, x, y; i <= n - 1; i++) {
        std::cin >> x >> y;
        tr[x].push_back(y);
        tr[y].push_back(x);
    }

    init1(root, 1, 0);
    init2(root, root);

    for(int i = 1, a, b; i <= m; i++) {
        std::cin >> a >> b;
        std::cout << lca(a, b) << '\n';
    }
}
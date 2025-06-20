//
// Created by guanghere on 25-4-12.
//
#include <assert.h>

#include <iostream>
#include <vector>

int n;
std::vector<int> siz, ans, back, tr;

void get_size(int now) {
    siz[now] = 1;
    if (now * 2 <= n) {
        get_size(now << 1);
        siz[now] += siz[now << 1];
    }
    if (now * 2 + 1 <= n) {
        get_size(now << 1 | 1);
        siz[now] += siz[now << 1 | 1];
    }
}

void cal(int l, int r, int root) {
    tr[root] = back[r];
    //assert(r - siz[root << 1 | 1] == l + siz[root << 1]);
    if (root * 2 + 1 <= n) {
        cal(r - siz[root << 1 | 1], r - 1, root << 1 | 1);
    }
    if (root * 2 <= n) {
        cal(l, l + siz[root << 1] - 1, root << 1);
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    std::cin >> n;
    siz.resize(n + 1);
    back.resize(n + 1);
    tr.resize(n + 1);
    get_size(1);
    for (int i = 1; i <= n; i++) {
        std::cin >> back[i];
    }
    cal(1, n, 1);
    for (int i = 1; i <= n; i++) {
        std::cout << tr[i] << " \n"[i == n];
    }
}
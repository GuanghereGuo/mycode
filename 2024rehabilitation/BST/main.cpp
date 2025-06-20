#include <algorithm>
#include <climits>
#include <cstdio>
using namespace std;
const int N = 2e5 + 10;
struct str {
    int l, r;
    int key, val;
    int cnt, size;
    explicit str(int l = 0, int r = 0, int key = 0, int val = 0, int cnt = 0,
        int size = 0)
        : l(l), r(r), key(key), val(val), cnt(cnt), size(size) {}
} tree[N];
int root, idx;
int new_tree(int key) {
    tree[++idx].key = key;
    tree[idx].val = rand();
    tree[idx].size = tree[idx].cnt = 1;
    return idx;
}
void pushup(int x) {
    tree[x].size = tree[tree[x].l].size + tree[tree[x].r].size + tree[x].cnt;
    return;
}
void zig(int &p) {
    int q = tree[p].l;
    tree[p].l = tree[q].r;
    tree[q].r = p;
    p = q;
    pushup(tree[p].r);
    pushup(p);
}
void zag(int &p) {
    int q = tree[p].r;
    tree[p].r = tree[q].l;
    tree[q].l = p;
    p = q;
    pushup(tree[p].l);
    pushup(p);
}
void m_build() {
    new_tree(INT_MIN);
    new_tree(INT_MAX);
    root = 1;
    tree[1].r = 2;
    pushup(1);
    if (tree[root].val < tree[tree[root].r].val) {
        zag(root);
    }
    return;
}
void m_insert(int &p, int key) {
    if (!p) {
        p = new_tree(key);
        return;
    }
    if (tree[p].key == key) {
        tree[p].cnt++;
    } else if (tree[p].key > key) {
        m_insert(tree[p].l, key);
        if (tree[tree[p].l].val > tree[p].val) {
            zig(p);
        }
    } else {
        m_insert(tree[p].r, key);
        if (tree[tree[p].r].val > tree[p].val) {
            zag(p);
        }
    }
    pushup(p);
}
void remove(int &p, int key) {
    if (tree[p].key == key) {
        if (tree[p].cnt > 1) {
            tree[p].cnt--;
        } else if (tree[p].l || tree[p].r) {
            if (!tree[p].r || tree[tree[p].l].val > tree[tree[p].r].val) {
                zig(p);
                remove(tree[p].r, key);
            } else if (!tree[p].l ||
                       tree[tree[p].l].val <= tree[tree[p].r].val) {
                zag(p);
                remove(tree[p].l, key);
            }
        } else {
            p = 0;
            return;
        }
    } else if (tree[p].key > key) {
        remove(tree[p].l, key);
    } else {
        remove(tree[p].r, key);
    }
    pushup(p);
}
int get_rank_by_val(int p, int key) {
    if (tree[p].key == key) {
        return tree[tree[p].l].size + 1;
    } else if (tree[p].key > key) {
        return get_rank_by_val(tree[p].l, key);
    } else {
        return tree[tree[p].l].size + tree[p].cnt +
               get_rank_by_val(tree[p].r, key);
    }
}
int get_val_by_rank(int p, int rank) {
    if (tree[tree[p].l].size >= rank)
        return get_val_by_rank(tree[p].l, rank);
    else if (tree[tree[p].l].size + tree[p].cnt >= rank)
        return tree[p].key;
    else
        return get_val_by_rank(tree[p].r,
                               rank - (tree[tree[p].l].size + tree[p].cnt));
}
int get_prev(int p, int key) {
    if (!p) return INT_MIN;
    if (tree[p].key == key) {
        return get_prev(tree[p].l, key);
    } else if (tree[p].key < key) {
        return max(tree[p].key, get_prev(tree[p].r, key));
    } else {
        return get_prev(tree[p].l, key);
    }
}
int get_next(int p, int key) {
    if (!p) return INT_MAX;
    if (tree[p].key == key) {
        return get_next(tree[p].r, key);
    } else if (tree[p].key > key) {
        return min(tree[p].key, get_next(tree[p].l, key));

    } else
        return get_next(tree[p].r, key);
}
int main() {
    int n;
    m_build();
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        int opt, p;
        scanf("%d%d", &opt, &p);
        if (opt == 1) {
            m_insert(root, p);
        } else if (opt == 2) {
            remove(root, p);
        } else if (opt == 3) {
            printf("%d\n", get_rank_by_val(root, p) - 1);
        } else if (opt == 4) {
            printf("%d\n", get_val_by_rank(root, p + 1));
        } else if (opt == 5) {
            printf("%d\n", get_prev(root, p));
        } else {
            printf("%d\n", get_next(root, p));
        }
    }
    return 0;
}
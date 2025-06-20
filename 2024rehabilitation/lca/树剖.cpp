//
// Created by 24087 on 24-9-30.
//
#include <functional>
#include <iostream>
#include <memory>
#include <vector>

template <class T>
class Segment_tree {
#define out_of_range() (r < tar_l || l > tar_r)
#define in_range() (tar_l <= l && r <= tar_r)
    struct node {
        T sum = 0;
        T add_lzy = 0;
        T mul_lzy = 1;  // 初始值！！！
    };
    // node_val == origin_val * mul_lzy + add_lzy
    int n, mod;
    std::vector<node> data;

    void pull_up(unsigned idx) {
        data[idx].sum = (data[idx << 1].sum + data[idx << 1 | 1].sum) % mod;
    }

    void make_add(unsigned idx, unsigned l, unsigned r, T val) {
        (data[idx].sum += val * (r - l + 1)) %= mod;
        (data[idx].add_lzy += val) %= mod;
    }

    void make_mul(unsigned idx, T val) {
        (data[idx].sum *= val) %= mod;
        (data[idx].add_lzy *= val) %= mod;
        (data[idx].mul_lzy *= val) %= mod;
    }

    void push_down(unsigned idx, unsigned l, unsigned r) {
        auto mid = l + (r - l) / 2;
        // mul firstly and add secondly
        // new_node_val == origin_val * mul_lzy_1 * mul_lzy_2 + add_lzy *
        // mul_lzy_2
        // + add_lzy_2
        make_mul(idx << 1, data[idx].mul_lzy);
        make_add(idx << 1, l, mid, data[idx].add_lzy);

        make_mul(idx << 1 | 1, data[idx].mul_lzy);
        make_add(idx << 1 | 1, mid + 1, r, data[idx].add_lzy);

        data[idx].add_lzy = 0;
        data[idx].mul_lzy = 1;
    }

    T ask(const unsigned idx, const unsigned l, const unsigned r,
          const unsigned tar_l, const unsigned tar_r) {
        if (out_of_range()) {
            return 0;
        }
        if (in_range()) {
            return data[idx].sum;
        }
        push_down(idx, l, r);
        auto mid = l + (r - l) / 2;
        return (ask(idx << 1, l, mid, tar_l, tar_r) +
                ask(idx << 1 | 1, mid + 1, r, tar_l, tar_r)) %
               mod;
    }

    void add(const unsigned idx, const unsigned l, const unsigned r,
             const unsigned tar_l, const unsigned tar_r, const T val) {
        if (out_of_range()) {
            return;
        }
        if (in_range()) {
            make_add(idx, l, r, val);
            return;
        }
        auto mid = l + (r - l) / 2;
        push_down(idx, l, r);
        add(idx << 1, l, mid, tar_l, tar_r, val);
        add(idx << 1 | 1, mid + 1, r, tar_l, tar_r, val);
        pull_up(idx);
    }

    void mul(const unsigned idx, const unsigned l, const unsigned r,
             const unsigned tar_l, const unsigned tar_r, const T val) {
        if (out_of_range()) {
            return;
        }
        if (in_range()) {
            make_mul(idx, val);
            return;
        }
        const auto mid = l + (r - l) / 2;
        push_down(idx, l, r);
        mul(idx << 1, l, mid, tar_l, tar_r, val);
        mul(idx << 1 | 1, mid + 1, r, tar_l, tar_r, val);
        pull_up(idx);
    }

   public:
    explicit Segment_tree(const std::vector<T> &nums,
                          const int &p = 571373) noexcept
        : n(nums.size()), mod(p), data(nums.size() * 4 + 5) {
        std::function<void(unsigned, unsigned, unsigned)> build_helper =
            [&](const unsigned idx, const unsigned l, const unsigned r) {
                if (l == r) {
                    data[idx].sum = nums[l - 1] % mod;  // 减一减一啊啊啊啊
                    return;
                }
                const auto mid = l + (r - l) / 2;
                build_helper(idx << 1, l, mid);
                build_helper(idx << 1 | 1, mid + 1, r);
                pull_up(idx);
            };
        build_helper(1, 1, n);
    }

    T ask(unsigned l, unsigned r) {
        if (r < l) {
            std::swap(l, r);
        }
        return ask(1, 1, n, l, r);
    }

    void add(unsigned l, unsigned r, T val) {
        if (r < l) {
            std::swap(l, r);
        }
        add(1, 1, n, l, r, val);
    }

    void mul(unsigned l, unsigned r, T val) {
        if (r < l) {
            std::swap(l, r);
        }
        mul(1, 1, n, l, r, val);
    }

#undef out_of_range
#undef in_range
};

int n, m, root, p;
std::unique_ptr<Segment_tree<long long>> ptr = nullptr;
std::vector<std::vector<int>> tr;
std::vector<int> father, siz, son, depth, top, dfn = {0}, rnk, ori;

void init1(int now, int dep, int fa) {
    father[now] = fa;
    depth[now] = dep;
    siz[now] = 1;
    son[now] = -1;
    for (const auto nxt : tr[now]) {
        if (depth[nxt]) {
            continue;
        }
        init1(nxt, dep + 1, now);
        siz[now] += siz[nxt];
        if (son[now] == -1 || siz[son[now]] < siz[nxt]) {
            son[now] = nxt;
        }
    }
}

void init2(int now, int tp) {
    static int cnt = 0;
    top[now] = tp;
    dfn[now] = ++cnt;
    rnk[cnt] = now;
    if (son[now] == -1) {
        return;
    }
    init2(son[now], tp);
    for (int i : tr[now]) {
        if (i == son[now] || i == father[now]) {
            continue;
        }
        init2(i, i);
    }
}

void init3() {
    std::vector<long long> vec(n);
    for (int i = 1; i <= n; i++) {
        vec[dfn[i] - 1] = ori[i];
    }
    ptr = std::make_unique<Segment_tree<long long>>(vec, p);
}

long long query_lca(int u, int v) {
    long long ans = 0;
    while (top[u] != top[v]) {
        if (depth[top[u]] < depth[top[v]]) {
            std::swap(u, v);
        }
        ans = (ans + ptr->ask(dfn[u], dfn[top[u]])) % p;
        u = father[top[u]];
    }
    ans = (ans + ptr->ask(dfn[u], dfn[v])) % p;
    return ans;
}

void modify_lca(int u, int v, int val) {
    while (top[u] != top[v]) {
        if (depth[top[u]] < depth[top[v]]) {
            std::swap(u, v);
        }
        ptr->add(dfn[u], dfn[top[u]], val);
        u = father[top[u]];
    }
    ptr->add(dfn[u], dfn[v], val);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    std::cin >> n >> m >> root >> p;

    tr.resize(n + 1);
    father.resize(n + 1);
    siz.resize(n + 1);
    son.resize(n + 1);
    depth.resize(n + 1);
    top.resize(n + 1);
    rnk.resize(n + 1);
    ori.resize(n + 1);
    dfn.resize(n + 1);

    for (int i = 1; i <= n; i++) {
        std::cin >> ori[i];
    }

    for (int i = 1, x, y; i <= n - 1; i++) {
        std::cin >> x >> y;
        tr[x].push_back(y);
        tr[y].push_back(x);
    }

    init1(root, 1, 0);
    init2(root, root);
    init3();

    for (int i = 1, x, y, z, _lca; i <= m; i++) {
        char opt;
        std::cin >> opt;
        long long res;
        switch (opt) {
            case '1':
                std::cin >> x >> y >> z;
                modify_lca(x, y, z);
                // for (int i = 1; i <= n; i++) {
                //     std::cerr << ptr->ask(i, i) << ' ';
                // }
                // std::cerr << '\n';
                break;
            case '2':
                std::cin >> x >> y;
                std::cout << query_lca(x, y) << '\n';
                break;
            case '3':
                std::cin >> x >> z;
                ptr->add(dfn[x], dfn[x] + siz[x] - 1, z);
                // for (int i = 1; i <= n; i++) {
                //     std::cerr << ptr->ask(i, i) << ' ';
                // }
                // std::cerr << '\n';
                break;
            case '4':
                std::cin >> x;
                std::cout << ptr->ask(dfn[x], dfn[x] + siz[x] - 1) << '\n';
                break;
            default:
                std::cerr << "ERR\n";
                break;
        }
    }
}
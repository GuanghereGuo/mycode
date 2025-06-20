#include <functional>
#include <iostream>
#include <memory>
#include <vector>

using ll = long long;

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

    T ask(const unsigned l, const unsigned r) { return ask(1, 1, n, l, r); }

    void add(const unsigned l, const unsigned r, T val) {
        add(1, 1, n, l, r, val);
    }

    void mul(const unsigned l, const unsigned r, T val) {
        mul(1, 1, n, l, r, val);
    }

#undef out_of_range
#undef in_range
};

int n, m, p;
std::unique_ptr<Segment_tree<ll>> ptr;

void init() {
    std::cin >> n >> m >> p;
    std::vector<ll> tmp;
    tmp.reserve(n);
    for (size_t i = 0; i < n; ++i) {
        int x;
        std::cin >> x;
        tmp.emplace_back(x);
    }

    ptr = std::make_unique<Segment_tree<ll>>(tmp, p);
}

void query() {
    for (size_t i = 0; i < m; ++i) {
        char opt;
        std::cin >> opt;
        if (opt == '1') {
            int l, r, val;
            std::cin >> l >> r >> val;
            ptr->mul(l, r, val);
        } else if (opt == '2') {
            int l, r, val;
            std::cin >> l >> r >> val;
            ptr->add(l, r, val);
        } else {
            int l, r;
            std::cin >> l >> r;
            std::cout << ptr->ask(l, r) << "\n";
        }
    }
}

void optimize_IO() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}

int main() {
    optimize_IO();
    init();
    query();
}

//
// Created by guanghere on 25-8-3.
//
#include <bits/stdc++.h>

using ll = long long;
using ull = unsigned long long;

class Hash {
    inline static ull mod = 1e9 + 9;
    inline static ull base1 = 998244353;
    inline static ull base2 = 1e9 + 7;

    [[nodiscard]] static ull mul(ull a, ull b) {
        // return a % mod * (b % mod) % mod;
        return a * b % mod;
    }
    [[nodiscard]] static ull add(ull a, ull b) {
        // return (a % mod + b % mod) % mod;
        return (a + b) % mod;
    }

    [[nodiscard]] static ull power(ull base, ull exp) {
        ull res = 1;
        while (exp > 0) {
            if (exp & 1) {
                res = mul(res, base);
            }
            base = mul(base, base);
            exp >>= 1;
        }
        return res;
    }
    [[nodiscard]] static ull overflow(ull base, ull exp) {
        ull res = 1;
        while (exp > 0) {
            if (exp & 1) {
                res = res * base;
            }
            base = base * base;
            exp >>= 1;
        }
        return res;
    }

    ull h1 = 0, h2 = 0;
    Hash(const ull h1, const ull h2) : h1(h1), h2(h2) {}

   public:
    Hash() = default;
    explicit Hash(const ull val)
        : h1(power(base1, val)), h2(overflow(base2, val)) {}

    Hash operator+(const Hash &other) const {
        return {add(h1, other.h1), h2 + other.h2};
    }
    Hash operator*(const Hash &other) const {
        return {mul(h1, other.h1), h2 * other.h2};
    }
    void operator+=(const Hash &other) {
        h1 = add(h1, other.h1);
        h2 += other.h2;
    }
    void operator*=(const Hash &other) {
        h1 = mul(h1, other.h1);
        h2 *= other.h2;
    }
    bool operator==(const Hash &other) const {
        return h1 == other.h1 && h2 == other.h2;
    }
};

class Segment_tree {
#define out_of_range() (r < tar_l || l > tar_r)
#define in_range() (tar_l <= l && r <= tar_r)
    struct node {
        Hash odd, even;
        Hash add_lzy = Hash(0);  // !!
    };

    int n, mod;
    std::vector<node> data;

    void pull_up(unsigned idx) {
        data[idx].odd = data[idx << 1].odd + data[idx << 1 | 1].odd;
        data[idx].even = data[idx << 1].even + data[idx << 1 | 1].even;
    }

    void make_add(unsigned idx, unsigned l, unsigned r, const Hash val) {
        // data[idx].odd +=  val * Hash(r - l + 1);
        // data[idx].even += val * Hash((r - l + 1));
        // data[idx].add_lzy += val;
        // 并非
        data[idx].odd *= val;
        data[idx].even *= val;
        data[idx].add_lzy *= val;
    }

    void push_down(unsigned idx, unsigned l, unsigned r) {
        if (data[idx].add_lzy == Hash(0)) {
            return;
        }

        auto mid = l + (r - l) / 2;
        make_add(idx << 1, l, mid, data[idx].add_lzy);
        make_add(idx << 1 | 1, mid + 1, r, data[idx].add_lzy);

        data[idx].add_lzy = Hash(0);
    }

    std::pair<Hash, Hash> ask(const unsigned idx, const unsigned l,
                              const unsigned r, const unsigned tar_l,
                              const unsigned tar_r) {
        if (out_of_range()) {
            // return {Hash(0), Hash(0)};
            return {Hash(), Hash()};  // !!
        }
        if (in_range()) {
            return {data[idx].odd, data[idx].even};
        }
        push_down(idx, l, r);
        auto mid = l + (r - l) / 2;
        auto left = ask(idx << 1, l, mid, tar_l, tar_r);
        auto right = ask(idx << 1 | 1, mid + 1, r, tar_l, tar_r);
        return {left.first + right.first, left.second + right.second};
    }

    void add(const unsigned idx, const unsigned l, const unsigned r,
             const unsigned tar_l, const unsigned tar_r, const Hash val) {
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

    void build_helper(const unsigned idx, const unsigned l, const unsigned r,
                      const std::vector<Hash> &nums) {
        if (l == r) {
            // data[idx].sum = nums[l - 1] % mod;
            if (l % 2 == 1) {
                data[idx].odd = nums[l - 1];
            } else {
                data[idx].even = nums[l - 1];
            }
            return;
        }
        const auto mid = l + (r - l) / 2;
        build_helper(idx << 1, l, mid, nums);
        build_helper(idx << 1 | 1, mid + 1, r, nums);
        pull_up(idx);
    };

   public:
    explicit Segment_tree(const std::vector<Hash> &nums,
                          const int &p = 571373) noexcept
        : n(nums.size()), mod(p), data(nums.size() * 4 + 5) {
        build_helper(1, 1, n, nums);
    }

    std::pair<Hash, Hash> ask(const unsigned l, const unsigned r) {
        return ask(1, 1, n, l, r);
    }

    void add(const unsigned l, const unsigned r, Hash val) {
        add(1, 1, n, l, r, val);
    }

#undef out_of_range
#undef in_range
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, q;
    std::cin >> n >> q;
    std::vector<Hash> nums(n);
    for (int i = 0, x; i < n; ++i) {
        std::cin >> x;
        nums[i] = Hash(x);
    }
    Segment_tree seg_tree(nums);
    while (q--) {
        int op, l, r;
        std::cin >> op >> l >> r;
        if (op == 0) {
            int val;
            std::cin >> val;
            seg_tree.add(l, r, Hash(val));
        } else {
            auto res = seg_tree.ask(l, r);
            std::cout << (res.first == res.second ? "Yes" : "No") << "\n";
        }
    }
}
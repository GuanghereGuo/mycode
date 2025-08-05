using ll = long long;
template <class T>
class Segment_tree
{
#define out_of_range() (r < tar_l || l > tar_r)
#define in_range() (tar_l <= l && r <= tar_r)
    struct node
    {
        T sum = 0;
        T add_lzy = 0;
    };

    int n, mod;
    std::vector<node> data;

    void pull_up(unsigned idx)
    {
        data[idx].sum = (data[idx << 1].sum + data[idx << 1 | 1].sum) % mod;
    }

    void make_add(unsigned idx, unsigned l, unsigned r, T val)
    {
        (data[idx].sum += val * (r - l + 1)) %= mod;
        (data[idx].add_lzy += val) %= mod;
    }

    void push_down(unsigned idx, unsigned l, unsigned r)
    {
        if (data[idx].add_lzy == 0)
        {
            return;
        }

        auto mid = l + (r - l) / 2;
        make_add(idx << 1, l, mid, data[idx].add_lzy);
        make_add(idx << 1 | 1, mid + 1, r, data[idx].add_lzy);

        data[idx].add_lzy = 0;
    }

    T ask(const unsigned idx, const unsigned l, const unsigned r,
          const unsigned tar_l, const unsigned tar_r)
    {
        if (out_of_range())
        {
            return 0;
        }
        if (in_range())
        {
            return data[idx].sum;
        }
        push_down(idx, l, r);
        auto mid = l + (r - l) / 2;
        return (ask(idx << 1, l, mid, tar_l, tar_r) +
                ask(idx << 1 | 1, mid + 1, r, tar_l, tar_r)) %
               mod;
    }

    void add(const unsigned idx, const unsigned l, const unsigned r,
             const unsigned tar_l, const unsigned tar_r, const T val)
    {
        if (out_of_range())
        {
            return;
        }
        if (in_range())
        {
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
    explicit Segment_tree(const std::vector<T> &nums,
                          const int &p = 571373) noexcept
        : n(nums.size()), mod(p), data(nums.size() * 4 + 5)
    {
        std::function<void(unsigned, unsigned, unsigned)> build_helper =
            [&](const unsigned idx, const unsigned l, const unsigned r)
        {
            if (l == r)
            {
                data[idx].sum = nums[l - 1] % mod;
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

    void add(const unsigned l, const unsigned r, T val)
    {
        add(1, 1, n, l, r, val);
    }

#undef out_of_range
#undef in_range
};
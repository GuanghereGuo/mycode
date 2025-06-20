long long pow(long long a, long long b, int p) {
    a %= p;//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    long long res = 1;
    while(b) {
        if(b & 1) {
            res = res * a % p;
        }
        a = a * a % p;
        b >>= 1;
    }
    return res;
}

class ChthollyTree {
    struct Node {
        int l, r;
        mutable long long val;
        Node(int l, int r, long long val) : l(l), r(r), val(val) {}
        bool operator<(const Node &x) const { return l < x.l; }
    };
    int n;
    std::set<Node> s;
    auto split(int x) {
        auto it = s.lower_bound(Node(x, 0, 0));
        if (it != s.end() && it->l == x) {
            return it;
        }
        --it;
        int l = it->l, r = it->r;
        long long val = it->val;
        s.erase(it);
        s.emplace(l, x - 1, val);
        return s.emplace(x, r, val).first;
    }

   public:
    explicit ChthollyTree(const int n) : n(n) {
        s.emplace(1, n, 0);  // 不用多插入一位
    }

    void assign(int l, int r, long long v) {
        const auto itr = split(r + 1);
        const auto itl = split(l);  // 先右后左，防止左边界迭代器失效
        s.erase(itl, itr);
        s.emplace(l, r, v);
    }

    void add(int l, int r, long long v) {
        for (auto itr = split(r + 1), itl = split(l); itl != itr; ++itl) {
            itl -> val += v;
        }
    }
    long long query_power(int l, int r,int x, int p) {
        long long res = 0;
        for (auto itr = split(r + 1), itl = split(l); itl != itr; ++itl) {
            (res += pow(itl->val, x, p) * (itl->r - itl->l + 1)) %= p;
        }
        return res;
    }
    long long get_x_th(int l, int r, int x) {
        std::map<long long, int> mp;
        for (auto itr = split(r + 1), itl = split(l); itl != itr; ++itl) {
            mp[itl->val] += itl->r - itl->l + 1;
        }
        for (const auto & [fst, snd] : mp) {
            if (x <= snd) {
                return fst;
            }
            x -= snd;
        }
        return -1;
    }
};
//
// Created by 24087 on 24-10-2.
//
#include <array>
#include <bit>
#include <iostream>
#include <vector>
#include <algorithm>

#define int long long

class Trie {
    struct Node {
        int end = 0, cnt = 0;
        std::array<int, 3> children = {0, 0};
        Node() = default;
    };
    static constexpr int root = 0;
    int tot = 0;
    std::vector<Node> data;
    std::vector<int> memory;
    static unsigned get_bit(unsigned x, unsigned i) { return (x >> i) & 1; }

   public:
    Trie():memory(0xfffff + 5) { data.emplace_back(); }
    void insert(unsigned val) {
        int now = root;
        data[now].cnt++;
        for (int i = 0; i < std::bit_width(val); i++) {
            if (data[now].children[get_bit(val, i)] == 0) {
                data[now].children[get_bit(val, i)] = ++tot;
                data.emplace_back();
            }
            if(data[now].children[2] == 0) {
                data[now].children[2] = ++tot;
                data.emplace_back();
            }
            now = data[now].children[get_bit(val, i)];
            data[now].cnt++;
        }
        data[now].end++;
    }
    int query(unsigned val, unsigned start = root, unsigned _i = 0) {
        if(start == root && _i == 0 &&memory[val]) {
            return memory[val];
        }
        int now = start, ans = 0;
        for (int i = _i; i < std::bit_width(val); i++) {
            if (get_bit(val, i) == 0) {
                ans += query(val | (1 << i), now, i);
            }
            if (data[now].children[get_bit(val, i)] == 0) {
                return ans;
            }
            now = data[now].children[get_bit(val, i)];
        }
        ans += data[now].cnt;
        if(start == root && _i == 0) {
            memory[val] = ans;
        }
        return ans;
    }
};

signed main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int t;
    std::cin >> t;

    while (t--) {
        int n;
        std::cin >> n;
        std::vector<int> vec(n);
        Trie trie;
        for (int i = 0; i < n; i++) {
            std::cin >> vec[i];
        }
        std::sort(vec.begin(), vec.end(), std::greater<>());
        int ans = 0;
        for (int i : vec) {
            trie.insert(i);
        }
        for (int i : vec) {
            ans += trie.query(i);
        }
        std::cout << ans << '\n';
    }
}
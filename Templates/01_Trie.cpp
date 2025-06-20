//
// Created by 24087 on 24-10-22.
//
#include <algorithm>
#include <array>
#include <bitset>
#include <iostream>
#include <vector>

class ZO_Trie {
    static bool get_bit(unsigned x, int i) { return (x >> i) & 1; }

    struct Node {
        std::array<size_t, 2> nxt = {0, 0};
        int is_end = 0;
        int is_suffix = 0;  // include end
    };
    static constexpr int root = 0;
    std::vector<Node> nodes;

   public:
    explicit ZO_Trie() : nodes(1) {}
    void insert(unsigned s) {
        size_t now = root;
        for (int i = 31; i >= 0; --i) {
            if (nodes[now].nxt[get_bit(s, i)] == 0) {
                nodes[now].nxt[get_bit(s, i)] = nodes.size();
                nodes.emplace_back();
            }
            now = nodes[now].nxt[get_bit(s, i)];
            nodes[now].is_suffix++;
        }
        nodes[now].is_end++;
    }
    [[nodiscard]] int count(const unsigned s) const {
        size_t now = root;
        for (int i = 31; i >= 0; --i) {
            if (nodes[now].nxt[get_bit(s, i)] == 0) {
                return 0;
            }
            now = nodes[now].nxt[get_bit(s, i)];
        }
        return nodes[now].is_suffix;
    }
    [[nodiscard]] unsigned find_max_xor(const unsigned s) const {
        size_t now = root;
        unsigned res = 0;
        for (int i = 31; i >= 0; --i) {
            if (nodes[now].nxt[!get_bit(s, i)] != 0) {
                res |= (1 << i);
                now = nodes[now].nxt[!get_bit(s, i)];
            } else {
                now = nodes[now].nxt[get_bit(s, i)];
            }
        }
        return res;
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    std::vector<unsigned> vec;

    int n, k;
    unsigned xor_val = 0;
    std::cin >> n >> k;
    ZO_Trie trie;
    trie.insert(0);

    for (unsigned i = 1, x; i <= n; ++i) {
        std::cin >> x;
        xor_val ^= x;
        vec.push_back(trie.find_max_xor(xor_val));
        trie.insert(xor_val);
    }

    std::sort(vec.begin(), vec.end(), std::greater<>());
    unsigned long long ans = 0;
    for(int i = 0; i < k; ++i) {
        ans += vec[i];
    }
    std::cout << ans;
}
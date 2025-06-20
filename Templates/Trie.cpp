//
// Created by 24087 on 24-10-22.
//
#include <vector>
#include <string>
#include <cctype>
#include <unordered_map>
#include <iostream>

class Trie {
    struct Node {
        std::unordered_map<char, size_t> nxt;
        int is_end = 0;
        int is_suffix = 0;//include end
    };
    static constexpr int root = 0;
    std::vector<Node> nodes;
public:
    explicit Trie() : nodes(1) {}
    void insert(const std::string &s) {
        size_t now = root;
        for (const char c : s) {
            if (!nodes[now].nxt.count(c)) {
                nodes[now].nxt[c] = nodes.size();
                nodes.emplace_back();
            }
            now = nodes[now].nxt[c];
            nodes[now].is_suffix++;
        }
        nodes[now].is_end++;
    }
    int count(const std::string &s) {
        size_t now = root;
        for (const char c : s) {
            if (!nodes[now].nxt.count(c)) {
                return 0;
            }
            now = nodes[now].nxt[c];
        }
        return nodes[now].is_suffix;
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int t;
    std::cin >> t;
    while(t--) {
        int n, q;
        std::cin >> n >> q;
        Trie trie;
        std::string s;
        while (n--) {
            std::cin >> s;
            trie.insert(s);
        }
        while (q--) {
            std::cin >> s;
            std::cout << trie.count(s) << '\n';
        }
    }
}
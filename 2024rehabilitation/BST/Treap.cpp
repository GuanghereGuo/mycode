//
// Created by guanghere on 25-7-16.
//
#include <bits/stdc++.h>

class Treap {
    struct Node {
        Node *ch[2];
        int val, cnt, siz;
        unsigned rank;
        explicit Node(const int v)
            : ch{nullptr, nullptr}, val(v), cnt(1), siz(1), rank(gen()) {
            ch[0] = ch[1] = nullptr;
        }
    };
    enum RotType { L = 1, R = 0 };
    Node *root = nullptr;
    inline static std::random_device rd;
    inline static std::mt19937 gen = std::mt19937(rd());

    static void update(Node *const now) {
        if (!now) return;
        now->siz = 1 + (now->ch[0] ? now->ch[0]->siz : 0) +
                   (now->ch[1] ? now->ch[1]->siz : 0);
    }

    static void rotate(Node *&now, const RotType type) {
        Node *tmp = now->ch[type];
        now->ch[type] = tmp->ch[1 ^ type];
        tmp->ch[1 ^ type] = now;
        update(now);
        update(tmp);
        now = tmp;
    }

    static void insert(Node *&now, const int x) {
        if (now == nullptr) {
            now = new Node(x);
            return;
        }
        if (x == now->val) {
            now->cnt++;
            // now->siz++;
        } else if (x < now->val) {
            insert(now->ch[0], x);
            if (now->ch[0]->rank > now->rank) {
                rotate(now, R);
            }
        } else {
            insert(now->ch[1], x);
            if (now->ch[1]->rank > now->rank) {
                rotate(now, L);
            }
        }
        update(now);
    }
    static void erase(Node *&now, const int x) {
        if (now == nullptr) return;
        if (x < now->val) {
            erase(now->ch[0], x);
        } else if (x > now->val) {
            erase(now->ch[1], x);
        } else {
            if (now->cnt > 1) {
                now->cnt--;
            } else {
                if (now->ch[0] == nullptr || now->ch[1] == nullptr) {
                    Node *tmp = now->ch[0] ? now->ch[0] : now->ch[1];
                    delete now;
                    now = tmp;
                } else {
                    if (now->ch[0]->rank < now->ch[1]->rank) {
                        rotate(now, R);
                        erase(now->ch[1], x);
                    } else {
                        rotate(now, L);
                        erase(now->ch[0], x);
                    }
                }
            }
        }
        update(now);
    }

    static int count_less(const Node *now, const int x) {
        if (now == nullptr) return 0;
        if (x > now->val) {
            return (now->ch[0] ? now->ch[0]->siz : 0) + now->cnt +
                   count_less(now->ch[1], x);
        }
        if (x == now->val) {
            return now->ch[0] ? now->ch[0]->siz : 0;
        }
        // x < now->val
        return count_less(now->ch[0], x);
    }

    static int find_by_rank(const Node *now, const int x) {
        int less_siz = now->ch[0] ? now->ch[0]->siz : 0;
        if (x <= less_siz) {
            return find_by_rank(now->ch[0], x);
        }
        if (x > less_siz + now->cnt) {
            return find_by_rank(now->ch[1], x - less_siz - now->cnt);
        }
        return now->val;
    }

    static int pre(const Node *now, const int x) {
        if (now == nullptr) return None;
        if (x < now->val) {
            return pre(now->ch[0], x);
        }
        if (x == now->val) {
            if (now->ch[0] == nullptr) {
                return None;  // 没有前驱
            }
            const Node *tmp = now->ch[0];
            while (tmp->ch[1]) {
                tmp = tmp->ch[1];
            }
            return tmp->val;
        }
        // x > now->val
        return now->ch[1] == nullptr ? now->val : pre(now->ch[1], x);
    }
    static int suf(const Node *now, const int x) {
        if (now == nullptr) return None;
        if (x < now->val) {
            return now->ch[0] == nullptr ? now->val : suf(now->ch[0], x);
        }
        if (x == now->val) {
            if (now->ch[1] == nullptr) {
                return None;  // 没有后继
            }
            const Node *tmp = now->ch[1];
            while (tmp->ch[0]) {
                tmp = tmp->ch[0];
            }
            return tmp->val;
        }
        // x > now->val
        return suf(now->ch[1], x);
    }

   public:
    static constexpr int None = INT_MAX;
    Treap() = default;
    void insert(const int x) { insert(root, x); }
    void erase(const int x) { erase(root, x); }
    [[nodiscard]] int rank(const int x) const {
        return count_less(root, x) + 1;
    }
    [[nodiscard]] int find_by_rank(const int x) const {
        if (x <= 0 || x > (root ? root->siz : 0)) {
            std::cerr << "Error: find_by_rank called with invalid rank: " << x
                      << ".\n";
            return None;
        }
        return find_by_rank(root, x);
    }
    [[nodiscard]] int pre(const int x) const {
        return pre(root, x);
    }
    [[nodiscard]] int suf(const int x) const {
        return suf(root, x);
    }
};

int main() {}
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct Node {
    ll value;
    int size;
    ll sum0, sum1;
    int prio;
    Node* left;
    Node* right;

    Node(ll v) : value(v), size(1), sum0(v), sum1(0), prio(rand()), left(nullptr), right(nullptr) {}
};

int get_size(Node* node) {
    return node ? node->size : 0;
}

void update(Node* node) {
    if (!node) return;
    int left_s = get_size(node->left);
    ll left_sum0 = node->left ? node->left->sum0 : 0;
    ll left_sum1 = node->left ? node->left->sum1 : 0;
    ll right_sum0 = node->right ? node->right->sum0 : 0;
    ll right_sum1 = node->right ? node->right->sum1 : 0;

    ll node_contrib0 = (left_s % 2 == 0) ? node->value : 0;
    ll node_contrib1 = (left_s % 2 == 1) ? node->value : 0;

    bool right_start_even = ((left_s + 1) % 2 == 0);
    ll right_contrib0 = right_start_even ? right_sum0 : right_sum1;
    ll right_contrib1 = right_start_even ? right_sum1 : right_sum0;

    node->sum0 = left_sum0 + node_contrib0 + right_contrib0;
    node->sum1 = left_sum1 + node_contrib1 + right_contrib1;
    node->size = 1 + left_s + get_size(node->right);
}

Node* merge(Node* l, Node* r) {
    if (!l) return r;
    if (!r) return l;
    if (l->prio > r->prio) {
        l->right = merge(l->right, r);
        update(l);
        return l;
    } else {
        r->left = merge(l, r->left);
        update(r);
        return r;
    }
}

pair<Node*, Node*> split(Node* node, int k) {
    if (!node) return {nullptr, nullptr};
    if (k <= get_size(node->left)) {
        auto [l, r] = split(node->left, k);
        node->left = r;
        update(node);
        return {l, node};
    } else {
        auto [l, r] = split(node->right, k - get_size(node->left) - 1);
        node->right = l;
        update(node);
        return {node, r};
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    srand(time(nullptr));

    int n, q;
    cin >> n >> q;
    vector<ll> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    Node* root = nullptr;
    for (int i = 0; i < n; ++i) {
        Node* new_node = new Node(a[i]);
        root = merge(root, new_node);
    }

    for (int i = 0; i < q; ++i) {
        int l, r;
        cin >> l >> r;
        l--; r--;  // Convert to 0-based

        auto [A, temp] = split(root, l);
        auto [B, C] = split(temp, r - l + 1);

        // Left cyclic shift on B: split into first 1 and rest, then merge rest + first
        auto [D, E] = split(B, 1);
        B = merge(E, D);

        // Merge back
        root = merge(A, merge(B, C));

        // Get sums
        ll sum_fish = root ? root->sum0 : 0;
        ll sum_man = root ? root->sum1 : 0;

        // Output result
        if (sum_fish > sum_man) {
            cout << "FISH\n";
        } else if (sum_man > sum_fish) {
            cout << "MAN\n";
        } else {
            cout << "TIE\n";
        }
    }

    return 0;
}
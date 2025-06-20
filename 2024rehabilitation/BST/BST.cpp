//
// Created by 24087 on 24-10-27.
//
#include <iostream>
#include <memory>

class BST {
    struct TreeNode {
        int key;
        std::unique_ptr<TreeNode> left;
        std::unique_ptr<TreeNode> right;
        int size;   // 当前节点为根的子树大小
        int count;  // 当前节点的重复数量

        explicit TreeNode(const int value)
            : key(value), size(1), count(1), left(nullptr), right(nullptr) {}
    };

    void inorderTraversal(const std::unique_ptr<TreeNode>& root) {
        if (root == nullptr) {
            return;
        }
        inorderTraversal(root->left);
        std::cout << root->key << " ";
        inorderTraversal(root->right);
    }

    int findMin(const std::unique_ptr<TreeNode>& root) {
        if (root == nullptr) {
            return -1;
        }
        const TreeNode* current = root.get();
        while (current->left != nullptr) {
            current = current->left.get();
        }
        return current->key;
    }

    int findMax(const std::unique_ptr<TreeNode>& root) {
        if (root == nullptr) {
            return -1;
        }
        const TreeNode* current = root.get();
        while (current->right != nullptr) {
            current = current->right.get();
        }
        return current->key;
    }

    bool search(const std::unique_ptr<TreeNode>& root, int target) {
        if (root == nullptr) {
            return false;
        }
        if (root->key == target) {
            return true;
        } else if (target < root->key) {
            return search(root->left, target);
        } else {
            return search(root->right, target);
        }
    }

    std::unique_ptr<TreeNode> insert(std::unique_ptr<TreeNode> root, int value) {
        if (root == nullptr) {
            return std::make_unique<TreeNode>(value);
        }
        if (value < root->key) {
            root->left = insert(std::move(root->left), value);
        } else if (value > root->key) {
            root->right = insert(std::move(root->right), value);
        } else {
            root->count++;  // 节点值相等，增加重复数量
        }
        root->size = root->count + (root->left ? root->left->size : 0) +
                     (root->right ? root->right->size : 0);  // 更新节点的子树大小
        return root;
    }

    std::unique_ptr<TreeNode> remove(std::unique_ptr<TreeNode> root, int value) {
        if (root == nullptr) {
            return root;
        }
        if (value < root->key) {
            root->left = remove(std::move(root->left), value);
        } else if (value > root->key) {
            root->right = remove(std::move(root->right), value);
        } else {
            if (root->count > 1) {
                root->count--;  // 节点重复数量大于1，减少重复数量
            } else {
                if (root->left == nullptr) {
                    return std::move(root->right);
                } else if (root->right == nullptr) {
                    return std::move(root->left);
                } else {
                    TreeNode* successor = findMinNode(root->right.get());
                    root->key = successor->key;
                    root->count = successor->count;  // 更新重复数量
                    successor->count = 1;
                    root->right = remove(std::move(root->right), successor->key);
                }
            }
        }
        return root;
    }

    TreeNode* findMinNode(TreeNode* root) {
        while (root->left != nullptr) {
            root = root->left.get();
        }
        return root;
    }

    int queryRank(const std::unique_ptr<TreeNode>& root, int v) {
        if (root == nullptr) return 0;
        if (root->key == v) return (root->left ? root->left->size : 0) + 1;
        if (root->key > v) return queryRank(root->left, v);
        return queryRank(root->right, v) + (root->left ? root->left->size : 0) +
               root->count;
    }

    int querykth(const std::unique_ptr<TreeNode>& root, int k) {
        if (root == nullptr) return -1;  // 或者根据需求返回其他合适的值
        if (root->left) {
            if (root->left->size >= k) return querykth(root->left, k);
            if (root->left->size + root->count >= k) return root->key;
        } else {
            if (k == 1) return root->key;
        }
        return querykth(root->right,
                        k - (root->left ? root->left->size : 0) - root->count);
    }

    std::unique_ptr<TreeNode> rt;

public:
    BST() : rt(nullptr) {}

    void insert(int value) { rt = insert(std::move(rt), value); }
    void remove(int value) { rt = remove(std::move(rt), value); }
    bool search(int target) { return search(rt, target); }
    int findMin() { return findMin(rt); }
    int findMax() { return findMax(rt); }
    void inorderTraversal() { inorderTraversal(rt); }
    int rank(int v) { return queryRank(rt, v); }
    int kth(int k) { return querykth(rt, k); }
    int pre(int v) {
        int res = -1;
        auto cur = rt.get();
        while (cur) {
            if (cur->key < v) {
                res = cur->key;
                cur = cur->right.get();
            } else {
                cur = cur->left.get();
            }
        }
        return res;
    }
    int aft(int v) {
        int res = -1;
        auto cur = rt.get();
        while (cur) {
            if (cur->key > v) {
                res = cur->key;
                cur = cur->left.get();
            } else {
                cur = cur->right.get();
            }
        }
        return res;
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);

    BST bst;
    int n;
    std::cin >> n;
    while (n--) {
        int opt, data;
        std::cin >> opt >> data;
        switch (opt) {
            case 2:
                bst.remove(data);
                break;
            case 3:
                std::cout << bst.rank(data) << std::endl;
                break;
            case 4:
                std::cout << bst.kth(data) << std::endl;
                break;
            case 5:
                std::cout << bst.pre(data) << std::endl;
                break;
            case 6:
                std::cout << bst.aft(data) << std::endl;
                break;
            case 1:
                bst.insert(data);
                break;
            default:
                break;
        }
    }

}
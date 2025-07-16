#include <iostream>
#include <memory>

// 二叉搜索树 (BST) 实现，支持重复键值
class BST {
    struct TreeNode {
        int key;                          // 节点键值
        std::unique_ptr<TreeNode> left;   // 左子树指针
        std::unique_ptr<TreeNode> right;  // 右子树指针
        int size;   // 以该节点为根的子树大小（包括重复节点）
        int count;  // 当前键值的重复次数

        explicit TreeNode(int value)
            : key(value), size(1), count(1), left(nullptr), right(nullptr) {}
    };

    // 中序遍历，用于调试或验证 BST 的有序性
    void inorderTraversal(const std::unique_ptr<TreeNode>& root) {
        if (!root) return;
        inorderTraversal(root->left);
        std::cout << root->key << " ";
        inorderTraversal(root->right);
    }

    // 查找最小值，时间复杂度 O(h)
    int findMin(const std::unique_ptr<TreeNode>& root) {
        if (!root) return -1;  // 空树返回 -1
        auto current = root.get();
        while (current->left) current = current->left.get();
        return current->key;
    }

    // 查找最大值，时间复杂度 O(h)
    int findMax(const std::unique_ptr<TreeNode>& root) {
        if (!root) return -1;  // 空树返回 -1
        auto current = root.get();
        while (current->right) current = current->right.get();
        return current->key;
    }

    // 搜索键值是否存在，时间复杂度 O(h)
    bool search(const std::unique_ptr<TreeNode>& root, int target) {
        if (!root) return false;
        if (root->key == target) return true;
        return target < root->key ? search(root->left, target)
                                  : search(root->right, target);
    }

    // 插入键值，时间复杂度 O(h)
    std::unique_ptr<TreeNode> insert(std::unique_ptr<TreeNode> root,
                                     int value) {
        if (!root) return std::make_unique<TreeNode>(value);
        if (value < root->key) {
            root->left = insert(std::move(root->left), value);
        } else if (value > root->key) {
            root->right = insert(std::move(root->right), value);
        } else {
            root->count++;  // 重复键值，增加计数
        }
        root->size = root->count + (root->left ? root->left->size : 0) +
                     (root->right ? root->right->size : 0);  // 更新子树大小
        return root;
    }

    // 删除键值，时间复杂度 O(h)
    std::unique_ptr<TreeNode> remove(std::unique_ptr<TreeNode> root,
                                     int value) {
        if (!root) return nullptr;
        if (value < root->key) {
            root->left = remove(std::move(root->left), value);
        } else if (value > root->key) {
            root->right = remove(std::move(root->right), value);
        } else {
            if (root->count > 1) {
                root->count--;  // 重复次数 > 1，仅减少计数
            } else if (!root->left) {
                return std::move(root->right);  // 无左子树，用右子树替换
            } else if (!root->right) {
                return std::move(root->left);  // 无右子树，用左子树替换
            } else {
                // 有两个子树，用右子树的最小节点（后继）替换
                auto successor = findMinNode(root->right.get());
                root->key = successor->key;
                root->count = successor->count;
                root->right = remove(std::move(root->right), successor->key);
            }
        }
        // 更新当前节点的子树大小
        root->size = root->count + (root->left ? root->left->size : 0) +
                     (root->right ? root->right->size : 0);
        return root;
    }

    // 辅助函数：查找以某节点为根的子树中的最小节点
    TreeNode* findMinNode(TreeNode* root) {
        while (root->left) root = root->left.get();
        return root;
    }

    // 查询键值的排名（小于该键值的节点数 + 1），时间复杂度 O(h)
    int queryRank(const std::unique_ptr<TreeNode>& root, int v) {
        if (!root) return 0;
        if (root->key == v) return (root->left ? root->left->size : 0) + 1;
        if (v < root->key) return queryRank(root->left, v);
        return queryRank(root->right, v) + (root->left ? root->left->size : 0) +
               root->count;
    }

    // 查询第 k 小元素，时间复杂度 O(h)
    int querykth(const std::unique_ptr<TreeNode>& root, int k) {
        if (!root || k <= 0 || k > root->size) return -1;  // 非法 k 或空树
        int leftSize = root->left ? root->left->size : 0;
        if (k <= leftSize) return querykth(root->left, k);  // 在左子树中
        if (k <= leftSize + root->count) return root->key;  // 当前节点即答案
        return querykth(root->right, k - leftSize - root->count);  // 在右子树中
    }

    // 查询小于 v 的最大键值（前驱），时间复杂度 O(h)
    int pre(const std::unique_ptr<TreeNode>& root, int v) {
        int res = -1;
        auto cur = root.get();
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

    // 查询大于 v 的最小键值（后继），时间复杂度 O(h)
    int aft(const std::unique_ptr<TreeNode>& root, int v) {
        int res = -1;
        auto cur = root.get();
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

    std::unique_ptr<TreeNode> rt;  // BST 的根节点

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
    int pre(int v) { return pre(rt, v); }
    int aft(int v) { return aft(rt, v); }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    BST bst;
    int n;
    std::cin >> n;
    while (n--) {
        int opt, data;
        std::cin >> opt >> data;
        switch (opt) {
            case 1:
                bst.insert(data);
                break;  // 插入
            case 2:
                bst.remove(data);
                break;  // 删除
            case 3:
                std::cout << bst.rank(data) << "\n";
                break;  // 查询排名
            case 4:
                std::cout << bst.kth(data) << "\n";
                break;  // 查询第 k 小
            case 5:
                std::cout << bst.pre(data) << "\n";
                break;  // 查询前驱
            case 6:
                std::cout << bst.aft(data) << "\n";
                break;  // 查询后继
            default:
                break;
        }
    }
    return 0;
}

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

// 定义支持重复元素和顺序统计的平衡树
// - pair<int, int>: 键为(x, cnt)，cnt用于区分重复的x
// - less<pair<int, int>>: 严格弱序，确保正确性
using ost = tree<pair<int, int>, null_type, less<pair<int, int>>, rb_tree_tag, tree_order_statistics_node_update>;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n; // 读取操作数
    ost t;    // 创建空的平衡树
    int cnt = 0; // 全局计数器，用于生成唯一标识符

    for (int i = 0; i < n; ++i) {
        int opt, x;
        cin >> opt >> x;

        if (opt == 1) {
            // 操作1：插入x
            t.insert({x, cnt++}); // 插入(x, cnt)，cnt递增确保唯一性
        } else if (opt == 2) {
            // 操作2：删除一个x（若存在）
            auto it = t.lower_bound({x, 0}); // 找到第一个>= (x, 0)的元素
            if (it != t.end() && it->first == x) {
                t.erase(it); // 删除该元素（只删除一个）
            }
        } else if (opt == 3) {
            // 操作3：查询比x小的数的个数并加一（即x的插入排名）
            cout << t.order_of_key({x, 0}) + 1 << '\n';
        } else if (opt == 4) {
            // 操作4：查询排名为x的数（从1开始）
            auto it = t.find_by_order(x - 1); // 排名从0开始，故x-1
            if (it != t.end()) {
                cout << it->first << '\n'; // 输出pair的first（即x）
            }
        } else if (opt == 5) {
            // 操作5：查询x的前驱（小于x的最大数）
            auto it = t.lower_bound({x, 0});
            if (it != t.begin()) {
                --it; // 向前一位即为前驱
                cout << it->first << '\n';
            }
            // 若无前驱（it == t.begin()），不输出
        } else if (opt == 6) {
            // 操作6：查询x的后继（大于x的最小数）
            auto it = t.upper_bound({x, INT_MAX}); // 第一个>(x, INT_MAX)的元素
            if (it != t.end()) {
                cout << it->first << '\n';
            }
            // 若无后继（it == t.end()），不输出
        }
    }

    return 0;
}

//
// Created by 24087 on 24-10-13.
//
#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
using namespace std;

// 计算数组的GCD
int calculate_gcd(const vector<int>& arr) {
    return accumulate(arr.begin(), arr.end(), 0, gcd<int, int>);
}

int main() {
    int T; // 测试用例个数
    cin >> T;

    while (T--) {
        int n, k;
        cin >> n >> k;

        vector<int> arr(n);
        for (int i = 0; i < n; i++) {
            cin >> arr[i];
        }

        if (k == 0) {
            cout << calculate_gcd(arr) << endl;
            continue;
        }

        int max_gcd = 0;
        for (int i = 0; i < n; i++) {
            int current_gcd = gcd(arr[i], k); // 当前元素与k的GCD
            max_gcd = max(max_gcd, current_gcd); // 更新最大GCD
        }

        // 输出结果
        cout << max_gcd << endl;
    }

    return 0;
}

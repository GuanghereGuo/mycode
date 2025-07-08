//
// Created by guanghere on 25-7-8.
//
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int t;
    cin >> t;
    for (int test = 0; test < t; ++test) {
        int n;
        cin >> n;
        vector<ll> a(n);
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
        }
        map<ll, int> freq;
        for (int k = 1; k <= n; ++k) {
            // 更新频率
            freq[a[k - 1]]++;
            // 获取当前前缀的不同值并排序
            vector<ll> v;
            for (const auto& p : freq) {
                v.push_back(p.first);
            }
            int m = v.size();
            // 计算频率的前缀和
            vector<ll> prefix(m + 1, 0);
            for (int i = 1; i <= m; ++i) {
                prefix[i] = prefix[i - 1] + freq[v[i - 1]];
            }
            double max_log_count = -1e300; // 初始化为极小值
            ll best_s = -1;
            // 遍历所有 (x, y) 对
            for (int i = 0; i < m; ++i) {
                for (int j = i; j < m; ++j) {
                    double log_count;
                    if (i == j) {
                        // x == y 的情况
                        log_count = freq[v[i]] * log(2.0);
                    } else {
                        // x < y，计算 c_between
                        ll sum_between = (j > i + 1 ? prefix[j] - prefix[i + 1] : 0);
                        log_count = freq[v[i]] * log(2.0) + freq[v[j]] * log(2.0) + sum_between * log(2.0);
                    }
                    ll s = v[i] + v[j];
                    // 更新最大值，若 log_count 相近则取 s 更大的
                    if (log_count > max_log_count + 1e-9 ||
                        (abs(log_count - max_log_count) < 1e-9 && s > best_s)) {
                        max_log_count = log_count;
                        best_s = s;
                        }
                }
            }
            cout << best_s << " ";
        }
        cout << "\n";
    }
    return 0;
}
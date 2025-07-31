//
// Created by guanghere on 25-7-28.
//
#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <functional>

// OI/ACM 风格的快速 I/O
void fast_io() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
}

// 封装查找 v_min 或 v_max 的逻辑
struct ExtremumResult {
    int v;
    int l;
    int r;
};

ExtremumResult find_extremum(int n, int k, const std::vector<int>& a, bool find_max) {
    auto check = [&](int v) -> std::pair<bool, std::pair<int, int>> {
        std::vector<int> p(n + 1, 0);
        for (int i = 0; i < n; ++i) {
            bool condition = find_max ? (a[i] >= v) : (a[i] <= v);
            p[i + 1] = p[i] + (condition ? 1 : -1);
        }

        int min_p_val = 0;
        int min_p_idx = 0;
        for (int r_idx = k; r_idx <= n; ++r_idx) {
            int l_p_idx_candidate = r_idx - k;
            if (p[l_p_idx_candidate] < min_p_val) {
                min_p_val = p[l_p_idx_candidate];
                min_p_idx = l_p_idx_candidate;
            }
            if (p[r_idx] > min_p_val) {
                return {true, {min_p_idx + 1, r_idx}};
            }
        }
        return {false, {0, 0}};
    };

    int low = 1, high = n, ans_v = (find_max ? 0 : n + 1);
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (check(mid).first) {
            ans_v = mid;
            if (find_max) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        } else {
            if (find_max) {
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }
    }

    auto [found, pair] = check(ans_v);
    return {ans_v, pair.first, pair.second};
}

// 计算子数组的中位数区间
std::pair<int, int> get_median_range(int l, int r, const std::vector<int>& a) {
    int len = r - l + 1;
    if (len == 0) return {0, 0};
    std::vector<int> sub;
    sub.reserve(len);
    for(int i = l - 1; i < r; ++i) {
        sub.push_back(a[i]);
    }

    int k_small = (len + 1) / 2 - 1; // 0-indexed
    std::nth_element(sub.begin(), sub.begin() + k_small, sub.end());
    int median_low = sub[k_small];

    int k_large = len / 2; // 0-indexed from the end
    std::nth_element(sub.begin(), sub.begin() + k_large, sub.end(), std::greater<int>());
    int median_high = sub[k_large];

    return {median_low, median_high};
}


void solve() {
    int n;
    int k;
    std::cin >> n >> k;
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    ExtremumResult max_res = find_extremum(n, k, a, true);
    ExtremumResult min_res = find_extremum(n, k, a, false);

    int v_min = min_res.v;
    int v_max = max_res.v;

    std::cout << v_max - v_min + 1 << "\n";

    if (v_max < v_min) return;

    auto range_max = get_median_range(max_res.l, max_res.r, a);
    auto range_min = get_median_range(min_res.l, min_res.r, a);

    int l_union = std::min(min_res.l, max_res.l);
    int r_union = std::max(min_res.r, max_res.r);
    auto range_union = get_median_range(l_union, r_union, a);

    std::vector<std::pair<int, int>> witnesses(n + 1);
    for (int v = range_min.first; v <= range_min.second; ++v) {
        if (v >= v_min && v <= v_max) witnesses[v] = {min_res.l, min_res.r};
    }
    for (int v = range_max.first; v <= range_max.second; ++v) {
        if (v >= v_min && v <= v_max) witnesses[v] = {max_res.l, max_res.r};
    }
    for (int v = range_union.first; v <= range_union.second; ++v) {
        if (v >= v_min && v <= v_max) witnesses[v] = {l_union, r_union};
    }

    for (int v = v_min; v <= v_max; ++v) {
        std::cout << v << " " << witnesses[v].first << " " << witnesses[v].second << "\n";
    }
}

int main() {
    fast_io();
    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}

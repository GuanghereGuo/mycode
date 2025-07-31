//
// Created by guanghere on 25-7-28.
//
#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

void solve() {
    int n;
    int k;
    std::cin >> n >> k;
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    auto check = [&](int v) -> bool {
        std::vector<int> p(n + 1, 0);
        for (int i = 0; i < n; ++i) {
            p[i + 1] = p[i] + (a[i] >= v ? 1 : -1);
        }

        int min_p_val = 0;
        for (int r = k; r <= n; ++r) {
            min_p_val = std::min(min_p_val, p[r - k]);
            if (p[r] >= min_p_val) {
                return true;
            }
        }
        return false;
    };

    int low = 1, high = n, ans_v = 0;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (check(mid)) {
            ans_v = mid;
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    std::vector<int> p(n + 1, 0);
    for (int i = 0; i < n; ++i) {
        p[i + 1] = p[i] + (a[i] >= ans_v ? 1 : -1);
    }

    int min_p_val = 0;
    int min_p_idx = 0;
    int final_l = 1, final_r = k;

    for (int r = k; r <= n; ++r) {
        if (p[r - k] < min_p_val) {
            min_p_val = p[r - k];
            min_p_idx = r - k;
        }

        if (p[r] >= min_p_val) {
            final_l = min_p_idx + 1;
            final_r = r;
            break;
        }
    }

    std::cout << ans_v << " " << final_l << " " << final_r << "\n";
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}

//
// Created by guanghere on 25-7-26.
//
#include <bits/stdc++.h>

#define int long long

signed main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;

    while (t--) {
        int n;
        std::cin >> n;
        std::vector<std::vector<int>> a(n + 1, std::vector<int>(n + 1));
        std::vector<int> minn(9, 1e12); // 0左上，1左下，2右上，3右下，4左，5右，6上，7下，8中心
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                std::cin >> a[i][j];
            }
        }

        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (i <= n / 2 + 1 && j <= n / 2 + 1) {
                    minn[0] = std::min(minn[0], a[i][j]);
                }
                if (i >= n / 2 + 1 && j <= n / 2 + 1) {
                    minn[1] = std::min(minn[1], a[i][j]);
                }
                if (i <= n / 2 + 1 && j >= n / 2 + 1) {
                    minn[2] = std::min(minn[2], a[i][j]);
                }
                if (i >= n / 2 + 1 && j >= n / 2 + 1) {
                    minn[3] = std::min(minn[3], a[i][j]);
                }
                if (i == n / 2 + 1 && j <= n / 2 + 1) {
                    minn[4] = std::min(minn[4], a[i][j]);
                }
                if (i == n / 2 + 1 && j >= n / 2 + 1) {
                    minn[5] = std::min(minn[5], a[i][j]);
                }
                if (i <= n / 2 + 1 && j == n / 2 + 1) {
                    minn[6] = std::min(minn[6], a[i][j]);
                }
                if (i >= n / 2 + 1 && j == n / 2 + 1) {
                    minn[7] = std::min(minn[7], a[i][j]);
                }
                if (i == n / 2 + 1 && j == n / 2 + 1) {
                    minn[8] = std::min(minn[8], a[i][j]);
                }

            }
        }
        std::vector<int> ans(5, 1e12);
        // 1个雷达
        ans[1] = minn[8];
        // 2个雷达
        ans[2] = std::min(minn[6] + minn[7], minn[5] + minn[4]);

        // 3个雷达
        ans[3] = 1e12;
        //左+右上+右下
        ans[3] = std::min(ans[3], minn[4] + minn[2] + minn[3]);
        //右+左上+左下
        ans[3] = std::min(ans[3], minn[5] + minn[0] + minn[1]);
        //上+左下+右下
        ans[3] = std::min(ans[3], minn[6] + minn[1] + minn[3]);
        //下+左上+右上
        ans[3] = std::min(ans[3], minn[7] + minn[0] + minn[2]);

        // 4个雷达
        ans[4] = minn[0] + minn[1] + minn[2] + minn[3];
        std::cout << std::min(std::min(ans[4], ans[1]), std::min(ans[2], ans[3])) << '\n';
    }
}
#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>

struct Gift {
    int d;
    int idx;
};

int main() {
    int n, K;
    std::cin >> n >> K;
    std::vector<Gift> gifts(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> gifts[i].d;
        gifts[i].idx = i;
    }
    std::sort(gifts.begin(), gifts.end(),
              [](const Gift& a, const Gift& b) { return a.d < b.d; });
    std::vector<int> sorted_d(n), original_indices(n);
    for (int i = 0; i < n; ++i) {
        sorted_d[i] = gifts[i].d;
        original_indices[i] = gifts[i].idx;
    }

    std::vector<long long> sumd(n + 1), sumsq(n + 1);
    for (int i = 0; i < n; ++i) {
        sumd[i + 1] = sumd[i] + sorted_d[i];
        sumsq[i + 1] = sumsq[i] + 1LL * sorted_d[i] * sorted_d[i];
    }

    const long long INF = LLONG_MAX / 2;
    std::vector<std::vector<long long>> dp(K + 1, std::vector<long long>(n, INF));
    std::vector<std::vector<int>> parent(K + 1, std::vector<int>(n, -1));

    for (int i = 0; i < n; ++i) {
        int cnt = i + 1;
        long long sum_d = sumd[i + 1] - sumd[0];
        long long sum_sq = sumsq[i + 1] - sumsq[0];
        long long day = sorted_d[i];
        dp[1][i] = cnt * day * day - 2 * day * sum_d + sum_sq;
    }

    for (int k_current = 2; k_current <= K; ++k_current) {
        for (int i = 0; i < n; ++i) {
            long long min_cost = INF;
            int best_j = -1;
            for (int j = 0; j < i; ++j) {
                if (dp[k_current - 1][j] == INF) continue;
                int cnt = i - j;
                long long sum_d = sumd[i + 1] - sumd[j + 1];
                long long sum_sq = sumsq[i + 1] - sumsq[j + 1];
                long long day = sorted_d[i];
                long long cost = cnt * day * day - 2 * day * sum_d + sum_sq;
                long long total = dp[k_current - 1][j] + cost;
                if (total < min_cost) {
                    min_cost = total;
                    best_j = j;
                }
            }
            if (min_cost != INF) {
                dp[k_current][i] = min_cost;
                parent[k_current][i] = best_j;
            }
        }
    }

    std::vector<std::pair<int, int>> groups;
    int current_k = K;
    int current_i = n - 1;
    while (current_k > 0) {
        if (current_k == 1) {
            groups.emplace_back(0, current_i);
            break;
        }
        int j = parent[current_k][current_i];
        groups.emplace_back(j + 1, current_i);
        current_i = j;
        current_k--;
    }
    std::reverse(groups.begin(), groups.end());

    std::vector<int> delivery_day(n);
    for (const auto& group : groups) {
        int day = sorted_d[group.second];
        for (int i = group.first; i <= group.second; ++i)
            delivery_day[i] = day;
    }

    std::vector<int> output(n);
    for (int i = 0; i < n; ++i)
        output[original_indices[i]] = delivery_day[i];

    for (int i = 0; i < n; ++i) {
        if (i) std::cout << " ";
        std::cout << output[i];
    }
    std::cout << "\n";
}
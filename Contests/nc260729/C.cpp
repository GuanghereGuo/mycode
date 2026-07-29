//
// Created by guanghere on 2026/7/29.
//
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct Node {
    ll f, g;
    int mask;
};

struct Compare {
    bool operator()(const Node &lhs, const Node &rhs) const {
        if (lhs.f != rhs.f) {
            return lhs.f > rhs.f;
        }
        const auto lhs_count = __builtin_popcount(lhs.mask);
        const auto rhs_count = __builtin_popcount(rhs.mask);
        if (lhs_count != rhs_count) {
            return lhs_count < rhs_count;
        }
        return lhs.g < rhs.g;
    }
};

int remove_bit(const int mask, const int bit) {
    const auto low = mask & ((1 << bit) - 1);
    const auto high = mask >> (bit + 1) << bit;
    return low | high;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    const auto state_count = 1 << m;
    const auto all = state_count - 1;
    const auto reduced_count = 1 << (m - 1);
    const auto reduced_all = reduced_count - 1;

    auto cost =
        vector<vector<ll>>(m, vector<ll>(reduced_count));
    auto reject_lower = vector<ll>(state_count);
    auto all_a_time = vector<ll>(m);

    for (auto i = 0; i < n; ++i) {
        auto time = vector<ll>(m);
        for (auto &x : time) {
            cin >> x;
        }

        string result;
        cin >> result;

        auto reject_mask = 0;
        for (auto j = 0; j < m; ++j) {
            if (result[j] == 'R') {
                reject_mask |= 1 << j;
            }
        }

        for (auto j = 0; j < m; ++j) {
            cost[j][remove_bit(reject_mask, j)] += time[j];
        }

        if (reject_mask == 0) {
            for (auto j = 0; j < m; ++j) {
                all_a_time[j] += time[j];
            }
        } else {
            auto min_reject_time = numeric_limits<ll>::max();
            for (auto j = 0; j < m; ++j) {
                if (reject_mask >> j & 1) {
                    min_reject_time = min(min_reject_time, time[j]);
                }
            }
            reject_lower[reject_mask] += min_reject_time;
        }
    }

    for (auto j = 0; j < m; ++j) {
        for (auto bit = 0; bit < m - 1; ++bit) {
            for (auto mask = 0; mask < reduced_count; ++mask) {
                if (mask >> bit & 1) {
                    cost[j][mask] += cost[j][mask ^ (1 << bit)];
                }
            }
        }
    }

    for (auto bit = 0; bit < m; ++bit) {
        for (auto mask = 0; mask < state_count; ++mask) {
            if (mask >> bit & 1) {
                reject_lower[mask] +=
                    reject_lower[mask ^ (1 << bit)];
            }
        }
    }

    const auto all_a_total =
        accumulate(all_a_time.begin(), all_a_time.end(), 0LL);
    auto heuristic = vector<ll>(state_count);
    for (auto mask = 1; mask < state_count; ++mask) {
        const auto bit = __builtin_ctz(mask);
        heuristic[mask] =
            heuristic[mask ^ (1 << bit)] + all_a_time[bit];
    }
    for (auto mask = 0; mask < state_count; ++mask) {
        heuristic[mask] =
            reject_lower[all ^ mask] + all_a_total - heuristic[mask];
    }
    reject_lower.clear();
    reject_lower.shrink_to_fit();

    constexpr auto inf = numeric_limits<ll>::max();
    auto dist = vector<ll>(state_count, inf);
    auto queue = priority_queue<Node, vector<Node>, Compare>{};

    dist[0] = 0;
    queue.push({heuristic[0], 0, 0});

    while (!queue.empty()) {
        const auto [f, g, mask] = queue.top();
        queue.pop();

        if (g != dist[mask]) {
            continue;
        }
        if (mask == all) {
            cout << g << '\n';
            return 0;
        }

        for (auto j = 0; j < m; ++j) {
            if (mask >> j & 1) {
                continue;
            }

            const auto next = mask | 1 << j;
            const auto reduced_mask = remove_bit(mask, j);
            const auto next_g =
                g + cost[j][reduced_all ^ reduced_mask];
            if (next_g < dist[next]) {
                dist[next] = next_g;
                queue.push({next_g + heuristic[next], next_g, next});
            }
        }
    }
}

#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
#include <utility>

using ll = long long;

auto find_path(ll start_a, ll start_b, ll target_c) -> std::vector<int> {
    if (start_a == target_c && start_b == target_c) {
        return {};
    }

    std::queue<std::pair<ll, ll>> q;
    q.emplace(start_a, start_b);

    std::map<std::pair<ll, ll>, std::pair<std::pair<ll, ll>, int>> parent;
    parent[{start_a, start_b}] = {{-1, -1}, 0};

    const ll MAX_VAL = 1LL << 34;

    while (!q.empty()) {
        auto [curr_a, curr_b] = q.front();
        q.pop();

        std::pair<ll, ll> next_states[4];
        next_states[0] = {curr_a * 2, curr_b};      // op 1: a <- a * 2
        next_states[1] = {curr_a, curr_b / 2};      // op 2: b <- b / 2
        next_states[2] = {curr_a ^ curr_b, curr_b}; // op 3: a <- a ^ b
        next_states[3] = {curr_a, curr_b ^ curr_a}; // op 4: b <- b ^ a

        for (int i = 0; i < 4; ++i) {
            auto [next_a, next_b] = next_states[i];
            int op_type = i + 1;

            if (next_a >= MAX_VAL || next_b >= MAX_VAL) {
                continue;
            }

            if (parent.find({next_a, next_b}) == parent.end()) {
                parent[{next_a, next_b}] = {{curr_a, curr_b}, op_type};

                if (next_a == target_c && next_b == target_c) {
                    std::vector<int> path;
                    std::pair<ll, ll> p = {next_a, next_b};
                    while (parent[p].second != 0) {
                        path.push_back(parent[p].second);
                        p = parent[p].first;
                    }
                    std::ranges::reverse(path);
                    return path;
                }

                q.emplace(next_a, next_b);
            }
        }
    }
    return {};
}

void solve() {
    ll a, b, c;
    std::cin >> a >> b >> c;

    auto path = find_path(a, b, c);

    if (a == c && b == c) {
        std::cout << 0 << "\n\n";
    } else if (!path.empty()) {
        std::cout << path.size() << "\n";
        for (size_t i = 0; i < path.size(); ++i) {
            std::cout << path[i] << (i == path.size() - 1 ? "" : " ");
        }
        std::cout << "\n";
    } else {
        std::cout << -1 << "\n";
    }
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
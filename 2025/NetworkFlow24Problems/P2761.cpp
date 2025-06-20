//
// Created by guanghere on 25-3-21.
//
#include <climits>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>

struct Patch {
    unsigned b1, b2, f1, f2;
    int cost;
    Patch(int c, std::string b, std::string f) : b1(0), b2(0), f1(0), f2(0), cost(c) {
        for (int i = 0; i < b.size(); i++) {
            if (b[i] == '+') {
                b1 |= 1 << i;
            } else if (b[i] == '-') {
                b2 |= 1 << i;
            }
        }
        for (int i = 0; i < f.size(); i++) {
            if (f[i] == '-') {
                f1 |= 1 << i;
            } else if (f[i] == '+') {
                f2 |= 1 << i;
            }
        }
    }
};

struct Node {
    int idx, dis;
    bool operator<(const Node& rhs) const {
        return dis > rhs.dis;
    }
    Node (int i, int d) : idx(i), dis(d) {}
};
struct my_int {
    int val = INT_MAX;
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, m;
    std::cin >> n >> m;
    std::vector<Patch> patches;
    for (int i = 0; i < m; i++) {
        int c;
        std::string b, f;
        std::cin >> c >> b >> f;
        patches.emplace_back(c, b, f);
    }
    unsigned start = (1 << n) - 1, end = 0;


    // Dijkstra
    std::unordered_map<unsigned, my_int> dis;
    std::unordered_set<unsigned> vis;
    std::priority_queue<Node> q;
    q.emplace(start, 0);
    dis[start].val = 0;

    while (!q.empty()) {
        int now = q.top().idx;
        q.pop();
        if (vis.contains(now)) continue;
        vis.insert(now);
        for (auto &patch : patches) {
            if ((now & patch.b1) != patch.b1 || (now & patch.b2) != 0) {
                continue;
            }
            unsigned next = (now & ~patch.f1) | patch.f2;
            if (dis[next].val - patch.cost > dis[now].val) {
                dis[next].val = dis[now].val + patch.cost;
                q.emplace(next, dis[next].val);
            }
        }
    }
    std::cout << (dis[end].val == INT_MAX ? 0 : dis[end].val) << '\n';
}
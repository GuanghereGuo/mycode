//
// Created by guanghere on 25-4-16.
//
#include <iostream>
#include <queue>
#include <vector>

enum Color {
    uf = 1,  // unset false
    st = 2,  // set true
    sf = 3,  // set false
    ut = 4,  // unset true
    err = 5
};

Color get_color(const std::string &s) {
    if (s == "set true") {
        return st;
    }
    if (s == "unset true") {
        return ut;
    }
    if (s == "set false") {
        return sf;
    }
    if (s == "unset false") {
        return uf;
    }
    std::cerr << "color error\n";
    return err;
}

bool check_set(const Color opt, bool &state) {
    if (opt == uf) return state == 0;
    if (opt == st) return state == 0 ? state = true : false;
    if (opt == sf) return state == 1;
    if (opt == ut) return state == 1 ? state = false, true : false;
    return false;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n;
    std::cin >> n;
    std::cin.ignore();
    std::vector<Color> color(n + 1);
    std::vector<std::vector<int>> g(n + 1);
    std::vector<int> cnt(5);

    for (int i = 1; i <= n; i++) {
        std::string s;
        std::getline(std::cin, s);
        color[i] = get_color(s);
        cnt[color[i]]++;
    }

    int m;
    std::cin >> m;
    std::vector<int> in_dgr(n + 1);
    for (int i = 1, u, v; i <= m; i++) {
        std::cin >> u >> v;
        g[u].push_back(v);
        in_dgr[v]++;
    }

    std::queue<int> q[5];
    for (int i = 1; i <= n; i++) {
        if (in_dgr[i] == 0) {
            q[color[i]].push(i);
        }
    }

    std::vector<int> ans;
    Color stage = uf;
    bool state = false;
    while (!q[1].empty() || !q[2].empty() || !q[3].empty() || !q[4].empty()) {
        if (q[uf].empty() && stage == uf) {
            stage = st;
        }
        for (int i = 2; i <= 4; i++) {
            if (q[i].empty() && stage == i) {
                if (cnt[i]) {
                    std::cout << -1;
                    return 0;
                }
                stage = static_cast<Color>(i + 1);
            }
        }
        if (stage == 5) {
            break;
        }
        int now = q[stage].front();
        q[stage].pop();
        cnt[stage]--;
        if (!check_set(stage, state)) {
            std::cout << -1;
            return 0;
        }
        ans.push_back(now);
        for (auto i : g[now]) {
            in_dgr[i]--;
            if (in_dgr[i] == 0) {
                q[color[i]].push(i);
            }
        }
    }
    while (!q[1].empty()) {
        int now = q[uf].front();
        q[uf].pop();
        cnt[uf]--;
        if (!check_set(uf, state)) {
            std::cout << -1;
            return 0;
        }
        ans.push_back(now);
        for (auto i : g[now]) {
            in_dgr[i]--;
            if (in_dgr[i] == 0) {
                q[color[i]].push(i);
            }
        }
    }

    for (auto i : ans) {
        std::cout << i << ' ';
    }
    
}

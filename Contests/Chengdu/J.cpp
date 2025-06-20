//
// Created by 24087 on 24-10-31.
//
#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;
    while(t--) {
        int n, m, q, mark = m;
        std::cin >> n >> m >> q;
        std::vector<bool> vis(m + 1);
        std::vector<long long> score(m + 1);

        for(int i = 1, opt, id, x, now = -1; i <= q; i++) {
            std::cin >> opt;
            switch (opt) {
                case 1:
                    std::cin >> now;
                    vis.assign(m + 1, false);
                    mark = m;
                    break;
                case 2:
                    std::cin >> id >> x;
                    if(x != now || vis[id]) {
                        continue;
                    }
                    score[id] += mark--;
                    vis[id] = true;
                    break;
                case 3:
                    std::cin >> id >> x;
                    if(x != now) {
                        continue;
                    }
                    vis[id] = true;
                    break;
                default:
                    std::cerr << "f_ck_ccf\n";
            }
        }
        std::vector<std::pair<long long, int>> vec;
        for(int i = 1; i <= m; i++) {
            vec.emplace_back(score[i], i);
        }
        using pll = std::pair<long long, int>;
        std::sort(vec.begin(), vec.end(), [](const pll &a, const pll &b) {
            return a.first == b.first ? a.second < b.second : a.first > b.first;
        });
        for(auto [s, i] : vec) {
            std::cout << i << ' ' << s << '\n';
        }
    }
}
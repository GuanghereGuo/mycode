//
// Created by guanghere on 2026/7/29.
//
#include <bits/stdc++.h>
using namespace std;

class KMP {
    std::string pattern;
    std::vector<int> pi;

   public:
    explicit KMP(const std::string &pattern)
        : pattern(pattern), pi(pattern.size()) {
        for (auto i = std::size_t{1}; i < pattern.size(); ++i) {
            auto j = pi[i - 1];
            while (j > 0 && pattern[i] != pattern[j]) {
                j = pi[j - 1];
            }
            if (pattern[i] == pattern[j]) {
                ++j;
            }
            pi[i] = j;
        }
    }

    [[nodiscard]] const auto &get_pi() const { return pi; }

    [[nodiscard]] auto find_all(const std::string &text) const {
        auto res = std::vector<int>{};
        if (pattern.empty()) {
            res.reserve(text.size() + 1);
            for (auto i = std::size_t{0}; i <= text.size(); ++i) {
                res.push_back(static_cast<int>(i));
            }
            return res;
        }

        auto j = 0;
        for (auto i = std::size_t{0}; i < text.size(); ++i) {
            while (j > 0 && text[i] != pattern[j]) {
                j = pi[j - 1];
            }
            if (text[i] == pattern[j]) {
                ++j;
            }
            if (j == static_cast<int>(pattern.size())) {
                res.push_back(static_cast<int>(i) - j + 1);
                j = pi[j - 1];
            }
        }
        return res;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        string s;
        int k;
        cin >> s >> k;

        string p = "Rounddo" + string(k, 'g');

        int n = s.size();
        int m = p.size();

        if (m > n) {
            cout << 0 << '\n';
            continue;
        }

        string a = s + s;
        vector<int> diff(n + 1);

        auto addRange = [&](int l, int r) {
            diff[l]++;
            diff[r + 1]--;
        };

        for (const auto start : KMP(p).find_all(a)) {
            const auto left = max(0, start - (n - m));
            const auto right = min(n - 1, start);
            if (left <= right) {
                addRange(left, right);
            }
        }

        int answer = 0;
        int cover = 0;

        for (int i = 0; i < n; ++i) {
            cover += diff[i];
            if (cover > 0)
                ++answer;
        }

        cout << answer << '\n';
    }
}

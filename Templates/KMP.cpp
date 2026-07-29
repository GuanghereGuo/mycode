#include <cstddef>
#include <string>
#include <vector>

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

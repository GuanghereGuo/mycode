//
// Created by guanghere on 25-6-3.
//
#include <iostream>
#include <vector>

struct Space {
    int w, l, h;
    bool operator<(const Space& b) const {
        return std::min(w, std::min(l, h)) < std::min(b.w, std::min(b.l, b.h));
    }
    Space() = default;
    Space(int w, int l, int h) : w(w), l(l), h(h) {}
};

int main() {
    std::vector<int> fib(11, 0);
    fib[1] = 1;
    fib[2] = 2;
    for (int i = 3; i <= 10; ++i) {
        fib[i] = fib[i - 1] + fib[i - 2];
    }

    int t;
    std::cin >> t;
    while (t--) {
        int n, m;
        std::cin >> n >> m;
        std::string result;
        for (int i = 0; i < m; ++i) {
            int w, l, h;
            std::cin >> w >> l >> h;
            Space space = {w, l, h};
            bool flag = true;
            for (int j = n; j >= 1; --j) {
                if (space < Space(fib[j], fib[j], fib[j])) {
                    result += '0';
                    flag = false;
                    break;
                } else {
                    if (space.w > space.l) {
                        if (space.h > space.w) {
                            space.h -= fib[j];
                        } else {
                            space.w -= fib[j];
                        }
                    } else {
                        if (space.h > space.l) {
                            space.h -= fib[j];
                        } else {
                            space.l -= fib[j];
                        }
                    }
                }
            }
            if (flag) {
                result += '1';
            }
        }
        std::cout << result << '\n';
    }
    return 0;
}
//
// Created by guanghere on 25-4-12.
//
#include <algorithm>
#include <iostream>
#include <vector>

struct Period {
    int begin, end;
    Period(int b, int e): begin(b), end(e){}
    bool operator<(const Period &rht) const {
        return end < rht.end;
    }
};

int get_time(std::string s) {
    int h = (s[0] - '0') * 10 + s[1] - '0';
    int m = (s[3] - '0') * 10 + s[4] - '0';
    int sec = (s[6] - '0') * 10 + s[7] - '0';
    return h * 3600 + m * 60 + sec;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n;
    std::cin >> n;
    std::vector<Period> vec;
    for (int i = 1; i <= n; i++) {
        std::string s1, s2;
        std::cin >> s1 >> s2;
        vec.emplace_back(get_time(s1), get_time(s2));
    }
    std::sort(vec.begin(), vec.end());
    int ans = 1, now = vec[0].end;
    for (int i = 1; i < vec.size(); i++) {
        if (vec[i].begin >= now) {
            now = vec[i].end;
            ans++;
        }
    }
    std::cout << ans;
}
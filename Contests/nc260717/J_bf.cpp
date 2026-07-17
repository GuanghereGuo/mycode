#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int get_card(std::string s) {
    int r;
    if (s[0] >= '2' && s[0] <= '9') {
        r = s[0] - '0';
    } else if (s[0] == 'T') {
        r = 10;
    } else if (s[0] == 'J') {
        r = 11;
    } else if (s[0] == 'Q') {
        r = 12;
    } else if (s[0] == 'K') {
        r = 13;
    } else {
        r = 14;
    }

    int c;
    if (s[1] == 'C') {
        c = 0;
    } else if (s[1] == 'D') {
        c = 1;
    } else if (s[1] == 'H') {
        c = 2;
    } else {
        c = 3;
    }

    return (r - 2) * 4 + c;
}

int get_rank(int card) { return card / 4 + 2; }

int get_suit(int card) { return card % 4; }

long long get_value(const std::vector<int> &h) {
    std::vector<int> cnt(15, 0);
    std::vector<int> r;

    bool flush = true;
    for (int card : h) {
        r.push_back(get_rank(card));
        cnt[get_rank(card)]++;
        if (get_suit(card) != get_suit(h[0])) {
            flush = false;
        }
    }
    std::sort(r.rbegin(), r.rend());

    bool different = true;
    for (int i = 1; i < 5; i++) {
        if (r[i] == r[i - 1]) {
            different = false;
        }
    }

    int straight = 0;
    if (different && r[0] - r[4] == 4) {
        straight = r[0];
    }
    if (r == std::vector<int>{14, 5, 4, 3, 2}) {
        straight = 5;
    }

    int four = 0;
    int three = 0;
    std::vector<int> pairs;
    std::vector<int> singles;

    for (int x = 14; x >= 2; x--) {
        if (cnt[x] == 4) {
            four = x;
        } else if (cnt[x] == 3) {
            three = x;
        } else if (cnt[x] == 2) {
            pairs.push_back(x);
        } else if (cnt[x] == 1) {
            singles.push_back(x);
        }
    }

    int type;
    std::vector<int> a(5);

    auto put_straight = [&]() {
        if (straight == 5) {
            a = {5, 4, 3, 2, 1};
        } else {
            for (int i = 0; i < 5; i++) {
                a[i] = straight - i;
            }
        }
    };

    if (flush && straight) {
        type = (straight == 14 ? 9 : 8);
        put_straight();
    } else if (four) {
        type = 7;
        a = {four, four, four, four, singles[0]};
    } else if (three && !pairs.empty()) {
        type = 6;
        a = {three, three, three, pairs[0], pairs[0]};
    } else if (flush) {
        type = 5;
        a = r;
    } else if (straight) {
        type = 4;
        put_straight();
    } else if (three) {
        type = 3;
        a = {three, three, three, singles[0], singles[1]};
    } else if (pairs.size() == 2) {
        type = 2;
        a = {pairs[0], pairs[0], pairs[1], pairs[1], singles[0]};
    } else if (pairs.size() == 1) {
        type = 1;
        a = {pairs[0], pairs[0], singles[0], singles[1], singles[2]};
    } else {
        type = 0;
        a = r;
    }

    long long value = type;
    for (int x : a) {
        value = value * 15 + x;
    }
    return value;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int T;
    std::cin >> T;

    while (T--) {
        std::vector<int> x(4);
        std::vector<int> y(4);
        std::vector<int> used(52, 0);

        for (int i = 0; i < 4; i++) {
            std::string s;
            std::cin >> s;
            x[i] = get_card(s);
            used[x[i]] = 1;
        }
        for (int i = 0; i < 4; i++) {
            std::string s;
            std::cin >> s;
            y[i] = get_card(s);
            used[y[i]] = 1;
        }

        std::vector<int> card;
        std::vector<long long> vx(52);
        std::vector<long long> vy(52);

        for (int c = 0; c < 52; c++) {
            if (used[c]) {
                continue;
            }

            card.push_back(c);

            std::vector<int> hx = x;
            std::vector<int> hy = y;
            hx.push_back(c);
            hy.push_back(c);
            vx[c] = get_value(hx);
            vy[c] = get_value(hy);
        }

        int ans = 1;

        // 8 张明牌外还有 44 张。Pierre 先选，我再从剩余 43 张中选。
        for (int p : card) {
            int best = -1;

            for (int q : card) {
                if (p == q) {
                    continue;
                }

                int now;
                if (vx[q] > vy[p]) {
                    now = 1;
                } else if (vx[q] == vy[p]) {
                    now = 0;
                } else {
                    now = -1;
                }
                best = std::max(best, now);
            }

            ans = std::min(ans, best);
        }

        if (ans == 1) {
            std::cout << "WoYaoYanPai\n";
        } else if (ans == -1) {
            std::cout << "GeiWoCaPiXie\n";
        } else {
            std::cout << "PaiMeiYouWenTi\n";
        }
    }

    return 0;
}

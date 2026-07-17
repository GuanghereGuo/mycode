#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int get_card(const std::string &s) {
    std::string ranks = "23456789TJQKA";
    std::string suits = "CDHS";
    return static_cast<int>(ranks.find(s[0]) * 4 + suits.find(s[1]));
}

std::vector<int> get_value(const std::vector<int> &h) {
    std::vector<int> cnt(15);
    std::vector<int> r;
    bool flush = true;

    for (int card : h) {
        int rank = card / 4 + 2;
        r.push_back(rank);
        cnt[rank]++;
        if (card % 4 != h[0] % 4) {
            flush = false;
        }
    }
    std::sort(r.rbegin(), r.rend());

    int straight = 0;
    if (std::adjacent_find(r.begin(), r.end()) == r.end() &&
        r[0] - r[4] == 4) {
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

    if (flush && straight) {
        return {straight == 14 ? 9 : 8, straight};
    }
    if (four) {
        return {7, four, singles[0]};
    }
    if (three && !pairs.empty()) {
        return {6, three, pairs[0]};
    }
    if (flush) {
        r.insert(r.begin(), 5);
        return r;
    }
    if (straight) {
        return {4, straight};
    }
    if (three) {
        return {3, three, singles[0], singles[1]};
    }
    if (pairs.size() == 2) {
        return {2, pairs[0], pairs[1], singles[0]};
    }
    if (pairs.size() == 1) {
        return {1, pairs[0], singles[0], singles[1], singles[2]};
    }

    r.insert(r.begin(), 0);
    return r;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int T;
    std::cin >> T;

    while (T--) {
        std::vector<int> a(4);
        std::vector<int> b(4);
        std::vector<int> used(52);

        for (int &card : a) {
            std::string s;
            std::cin >> s;
            card = get_card(s);
            used[card] = 1;
        }
        for (int &card : b) {
            std::string s;
            std::cin >> s;
            card = get_card(s);
            used[card] = 1;
        }

        std::vector<int> can;
        std::vector<std::vector<int>> va(52);
        std::vector<std::vector<int>> vb(52);

        for (int card = 0; card < 52; card++) {
            if (used[card]) {
                continue;
            }

            can.push_back(card);

            std::vector<int> ha = a;
            std::vector<int> hb = b;
            ha.push_back(card);
            hb.push_back(card);
            va[card] = get_value(ha);
            vb[card] = get_value(hb);
        }

        int first = -1;
        int second = -1;

        for (int card : can) {
            if (first == -1 || va[card] > va[first]) {
                second = first;
                first = card;
            } else if (second == -1 || va[card] > va[second]) {
                second = card;
            }
        }

        int ans = 1;

        for (int p : can) {
            int q = (p == first ? second : first);

            if (va[q] < vb[p]) {
                ans = -1;
                break;
            }
            if (va[q] == vb[p]) {
                ans = 0;
            }
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

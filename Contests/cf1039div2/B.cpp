//
// Created by guanghere on 25-7-27.
//
#include <algorithm>
#include <deque>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

bool is_valid_move(int value, const std::deque<int>& q_suffix) {
    if (q_suffix.size() < 4) {
        return true;
    }

    std::vector<int> temp;
    temp.reserve(5);
    for (int val : q_suffix) {
        temp.push_back(val);
    }
    temp.push_back(value);

    bool increasing = true;
    for (size_t i = 0; i < 4; ++i) {
        if (temp[i] >= temp[i + 1]) {
            increasing = false;
            break;
        }
    }
    if (increasing) return false;

    bool decreasing = true;
    for (size_t i = 0; i < 4; ++i) {
        if (temp[i] <= temp[i + 1]) {
            decreasing = false;
            break;
        }
    }
    if (decreasing) return false;

    return true;
}

void add_to_suffix(std::deque<int>& q_suffix, int value) {
    q_suffix.push_back(value);
    if (q_suffix.size() > 4) {
        q_suffix.pop_front();
    }
}

bool is_next_state_dead(int next_l_val, int next_r_val, bool is_last_element,
                        const std::deque<int>& next_q_suffix) {
    bool can_take_l = is_valid_move(next_l_val, next_q_suffix);
    if (is_last_element) {
        return !can_take_l;
    }
    bool can_take_r = is_valid_move(next_r_val, next_q_suffix);
    return !can_take_l && !can_take_r;
}

void solve() {
    int n;
    std::cin >> n;
    std::deque<int> p(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> p[i];
    }

    std::string result = "";
    std::deque<int> q_suffix;

    while (!p.empty()) {
        if (p.size() == 1) {
            result += 'L';
            break;
        }

        int left_val = p.front();
        int right_val = p.back();

        bool can_l = is_valid_move(left_val, q_suffix);
        bool can_r = is_valid_move(right_val, q_suffix);

        bool take_l;

        if (can_l && can_r) {
            std::deque<int> next_q_suffix_if_l = q_suffix;
            add_to_suffix(next_q_suffix_if_l, left_val);

            bool l_leads_to_dead_end = is_next_state_dead(
                p[1], p.back(), p.size() == 2, next_q_suffix_if_l);

            if (l_leads_to_dead_end) {
                take_l = false;
            } else {
                take_l = true;
            }
        } else if (can_l) {
            take_l = true;
        } else {
            take_l = false;
        }

        if (take_l) {
            result += 'L';
            add_to_suffix(q_suffix, left_val);
            p.pop_front();
        } else {
            result += 'R';
            add_to_suffix(q_suffix, right_val);
            p.pop_back();
        }
    }
    std::cout << result << "\n";
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

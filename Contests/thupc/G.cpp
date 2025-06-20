//
// Created by guanghere on 24-12-15.
//
#include <iostream>
#include <vector>
#include <string>
using namespace std;

void count_intervals(const string& s, int& full_w, int& full_m, int& wm, int& mw, int& mm, int& ww) {
    int n = s.size();
    int start = 0;

    while (start < n) {
        if (s[start] == 'X') {
            start++;
            continue;
        }

        int end = start;
        while (end < n && s[end] != 'X') {
            end++;
        }

        bool has_w = false, has_m = false;
        char first = s[start], last = s[end - 1];

        for (int i = start; i < end; i++) {
            if (s[i] == 'W') has_w = true;
            if (s[i] == 'M') has_m = true;
        }

        if (has_w && !has_m) full_w++;
        else if (!has_w && has_m) full_m++;
        else if (first == 'W' && last == 'M') wm++;
        else if (first == 'M' && last == 'W') mw++;
        else if (first == 'M' && last == 'M') mm++;
        else if (first == 'W' && last == 'W') ww++;

        start = end;
    }
}

string determine_winner(const string& s) {
    int full_w = 0, full_m = 0, wm = 0, mw = 0, mm = 0, ww = 0;
    count_intervals(s, full_w, full_m, wm, mw, mm, ww);
    //std::cerr << "full_w: " << full_w << ", full_m: " << full_m << ", wm: " << wm << ", mw: " << mw << ", mm: " << mm << ", ww: " << ww << endl;

    bool w_turn = true;
    while (true) {
        if (w_turn) {
            if (full_w > 0) {
                full_w--;
            } else if (wm > 0) {
                wm--;
                full_m++;
            } else if (mw > 0) {
                mw--;
                full_m++;
            } else if (ww > 0) {
                ww--;
            } else if (mm > 0) {
                mm--;
                full_m++;
            }
            if (full_w == 0 && mw == 0 && wm == 0 && ww == 0 && mm == 0) {
                if (full_m == 0 && mw == 0 && wm == 0 && ww == 0 && mm == 0) {
                    return "Draw";
                }
                return "Water";
            }
        } else {
            if (full_m > 0) {
                full_m--;
            } else if (mw > 0) {
                mw--;
                full_w++;
            } else if (wm > 0) {
                wm--;
                full_w++;
            } else if (mm > 0) {
                mm--;
            } else if (ww > 0) {
                ww--;
                full_w++;
            }
            if (full_m == 0 && mw == 0 && wm == 0 && ww == 0 && mm == 0) {
                if (full_w == 0 && mw == 0 && wm == 0 && mm == 0 && ww == 0) {
                    return "Draw";
                }
                return "Menji";
            }
        }

        w_turn = !w_turn;
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int t;
    std::cin >> t;
    while (t--) {
        string s;
        cin >> s;
        cout << determine_winner(s) << endl;
    }
    return 0;
}

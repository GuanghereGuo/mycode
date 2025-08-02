//
// Created by guanghere on 25-8-2.
//
#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <limits>

using namespace std;

long long calculate_score(long long n, const vector<long long>& v, const vector<long long>& l, bool maximize) {
    if (n == 0) {
        return 0;
    }

    long long best_score = maximize ? numeric_limits<long long>::min() : numeric_limits<long long>::max();

    vector<int> p = {0, 1, 2};

    do {
        vector<long long> temp_v = v;
        vector<long long> temp_l = l;
        long long wins = 0;
        long long losses = 0;

        int l_type;
        for (int v_type : p) {
            long long m;
            if (maximize) {
                l_type = (v_type + 1) % 3;
                m = min(temp_v[v_type], temp_l[l_type]);
                wins += m;
            } else {
                l_type = (v_type + 2) % 3;
                m = min(temp_v[v_type], temp_l[l_type]);
                losses += m;
            }
            temp_v[v_type] -= m;
            temp_l[l_type] -= m;
        }

        long long ties = 0;
        for (int i = 0; i < 3; ++i) {
            long long m = min(temp_v[i], temp_l[i]);
            ties += m;
        }

        long long remaining_games = n - (maximize ? wins : losses) - ties;
        if (maximize) {
            losses = remaining_games;
        } else {
            wins = remaining_games;
        }

        long long current_score = wins - losses;

        if (maximize) {
            best_score = max(best_score, current_score);
        } else {
            best_score = min(best_score, current_score);
        }

    } while (ranges::next_permutation(p).found);

    return best_score;
}

void solve() {
    long long n, r1, s1, p1, r2, s2, p2;
    cin >> n >> r1 >> s1 >> p1 >> r2 >> s2 >> p2;

    vector<long long> v = {r1, s1, p1};
    vector<long long> l = {r2, s2, p2};

    long long max_s = calculate_score(n, v, l, true);

    long long min_s = calculate_score(n, v, l, false);

    cout << max_s << " " << min_s << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
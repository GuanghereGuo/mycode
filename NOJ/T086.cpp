//
// Created by 24087 on 24-9-28.
//
#include <iostream>
#include <string>
using namespace std;

bool is_sum_string(const string& s, const int start, const int len1,
                   const int len2) {
    if (start + len1 + len2 >= s.size()) {
        return false;
    }

    const long long num1 = stoll(s.substr(start, len1));
    const long long num2 = stoll(s.substr(start + len1, len2));

    const long long target_sum = num1 + num2;

    string sum_str = to_string(target_sum);

    int next_start = start + len1 + len2;
    int next_len = sum_str.size();

    if (stoll(s.substr(next_start, next_len)) == target_sum) {
        // If we reach the end of the string and it matches, return true
        if (next_start + next_len == s.size()) {
            return true;
        }
        // Recur to check the rest of the string
        return is_sum_string(s, start + len1, len2, next_len);
    }

    return false;
}

bool is_sum_string(const string& s) {
    const auto n = s.size();
    for (int len1 = 1; len1 <= n / 2; len1++) {
        for (int len2 = 1; len2 <= n / 2; len2++) {
            if (is_sum_string(s, 0, len1, len2)) {
                return true;
            }
        }
    }
    return false;
}

int main() {
    string str;
    cin >> str;
    if (is_sum_string(str)) {
        cout << "true" << endl;
    } else {
        cout << "false" << endl;
    }
}

//
// Created by guanghere on 25-3-23.
//
#include <iostream>
using namespace std;

int get_digit(long long n, int m) {
    while (true) {
        if (n == 1) {
            return (m == 0) ? 1 : 0;
        }
        if (n % 2 == 0) {  // n even
            int last_block_len = 2;  // "11"
            if (m < last_block_len) {
                return 1;  // Both digits are 1
            }
            m -= last_block_len;
            n -= 1;
        } else {  // n odd (including n=1, but handled above)
            int last_block_len = 3;  // "101" for n >= 3
            if (m < last_block_len) {
                return (m == 1) ? 0 : 1;  // "101" → 1,0,1 from right
            }
            m -= last_block_len;
            n -= 1;
        }
    }
}

int main() {
    int t;
    cin >> t;
    for (int i = 0; i < t; ++i) {
        long long n;
        int m;
        cin >> n >> m;
        cout << get_digit(n, m) << endl;
    }
    return 0;
}
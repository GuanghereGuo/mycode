//
// Created by guanghere on 25-4-6.
//
#include <iostream>
#include <string>
using namespace std;
int n, T;
string s1, s2;
int main() {
    cin >> T;
    while (T--) {
        cin >> n;
        cin >> s1 >> s2;
        int flag = 0, noflag = 0;
        if (n == 1) {
            if ((s1[0] == '#') ^ (s2[0] == '#')) {
                std::cout << "None" << std::endl;
                continue;
            } else {
                std::cout << "Unique" << std::endl;
                continue;
            }
        }
        for (int i = 0; i < n; i++) {
            if (s1[i] == '.' && s2[i] == '.') {
                s1[i] = s2[i] = '#';
                if (i + 1 < n && s1[i + 1] == '.' && s2[i + 1] == '.') {
                    flag = 1;
                }
            } else if (s1[i] == '.' && s2[i] == '#') {
                if (i + 1 >= n || s1[i + 1] == '#') {
                    noflag = 1;
                    break;
                }
                s1[i] = s1[i + 1] = '#';
            } else if (s1[i] == '#' && s2[i] == '.') {
                if (i + 1 >= n || s2[i + 1] == '#') {
                    noflag = 1;
                    break;
                }
                s2[i] = s2[i + 1] = '#';
            }
        }
        if (noflag) {
            cout << "None" << endl;
        } else {
            if (flag) {
                cout << "Multiple" << endl;
            } else {
                cout << "Unique" << endl;
            }
        }
    }
}
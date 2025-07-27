//
// Created by guanghere on 25-7-24.
//
#include <bits/stdc++.h>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    int A[61][61];

    for (int i = 0; i <= 60; ++i) {
        for (int j = 0; j <= 60; ++j) {
            A[i][j] = 0;
        }
    }

    for (int i = 1; i <= 30; ++i) {
        for (int j = i; j <= 30; ++j) {
            A[i][j] = 1;
        }
        if (i == 1) {
            for (int j = 1; j <= 30; ++j) {
                A[i][j] = 1;
            }
        }
    }

    for (int i = 1; i <= 30; ++i) {
        A[i][i + 30] = 1;
    }
    for (int i = 31; i <= 60; ++i) {
        A[i][i] = 1;
    }

    for (int i = 1; i <= 60; i++) {
        if ((n >> (i - 1)) & 1) {
            A[i][1] = 1;
        }
    }
    for (int i = 1; i <= 60; i++) {
        for (int j = 1; j <= 60; j++) {
            std::cout << A[i][j] << " \n"[j == 60];
        }
    }
}

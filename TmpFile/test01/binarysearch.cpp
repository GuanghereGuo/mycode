//
// Created by 24087 on 24-12-10.
//
#include <stdio.h>

//a_n = n * (n + 1) / 2;

int main() {
    int target;
    scanf("%d", &target);
    int l = 0, r = target;
    while (l + 1 != r) {
        int mid = (l + r) / 2;
        if (1ll * mid * (mid + 1) / 2 < target) {
            l = mid;
        } else {
            r = mid;
        }
    }
    printf("%d\n", r);
    return 0;
}

#include <stdio.h>
int main() {
    int n;
    scanf("%d", &n);
    int a = n / 100;
    int b = n / 10 % 10;
    int c = n % 10;
    for (int i = 1; i < a; i++) {
        for (int j = i + 1; j <= 9; j++) {
            for (int k = j + 1; k <= 9; k++) {
                printf("%d%d%d ", i, j, k);
            }
        }
    }
    for (int j = a + 1; j <= b; j++) {
        for (int k = j + 1; k <= 9; k++) {
            printf("%d%d%d ", i, j, k);
        }
    }
    return 0;
}
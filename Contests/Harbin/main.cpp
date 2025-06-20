#include <iostream>
#include <cmath>
#include <cstdlib>

using namespace std;
bool d1(int i) {
    char k[32] = {0};
    //itoa(i, k, 10);
    int w1 = 0, w2 = int(log10(i));
    while (w1 < w2) {
        if (k[w1] != k[w2]) return false;
        w1++;
        w2--;
    }
    return true;
}
bool d2(const int *s) {
    int i = 31;
    while (s[i] == 0) i--;
    int j = 0;
    while (j < i) {
        if (s[i] != s[j]) return false;
        j++;
        i--;
    }
    return true;
}
int main() {
    int n, k, sum = 0;
    int s[32] = {0};
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        int j = 0;
        s[0]++;
        while (s[j] == k) {
            s[j] = 0;
            j++;
            s[j]++;
        }
        if (d1(i) && d2(s)) sum += i;
    }
    cout << sum;
    return 0;
}
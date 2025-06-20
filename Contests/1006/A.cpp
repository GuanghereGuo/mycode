//
// Created by 24087 on 24-10-6.
//
#include <iostream>
using namespace std;

int ans;
int v[] = {1, 6, 28, 88, 198, 328, 648}, av[] = {8, 18, 28, 58, 128, 198, 388};

void dfs(int pl, int n, int pri) {
    if (v[pl] > n)
        ans = max(ans, pri + n * 10);
    else if (pl == 7)
        ans = max(ans, pri + n * 10);
    else {
        dfs(pl + 1, n, pri);
        dfs(pl + 1, n - v[pl], pri + v[pl] * 10 + av[pl]);
    }
}

int main() {
    int n;
    cin >> n;
    dfs(0, n, 0);
    cout << ans << endl;
    return 0;
}

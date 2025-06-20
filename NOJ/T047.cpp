//
// Created by 24087 on 24-10-9.
//
#include <iostream>
#include <vector>

constexpr int max_size = 301;


int pre_sum[max_size][max_size] = {{0}};
int arr[max_size][max_size] = {{0}};

//求前缀和
void get_prefix(int n, int m) {
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            pre_sum[i][j] = pre_sum[i - 1][j] + pre_sum[i][j - 1]
                           - pre_sum[i - 1][j - 1] + arr[i][j];
        }
    }
}

int calculate_sum(int x1, int x2, int y1, int y2) {
    return pre_sum[x2][y2] - pre_sum[x1 - 1][y2] - pre_sum[x2][y1 - 1]
           + pre_sum[x1 - 1][y1 - 1];
}

bool is_perfect(int x1, int x2, int y1, int y2) {
    int outer = calculate_sum(x1, x2, y1, y2), inner;
    int len = 2 * (x2 - x1 + y2 - y1);
    if ((x2 - x1) == 1 || (y2 - y1) == 1) inner = 0;
    else inner = calculate_sum(x1 + 1, x2 - 1, y1 + 1, y2 - 1);

    if (inner != 1 && inner != 0 && inner != -1) return false;
    if ((outer - inner) != len) return false;
    return true;
}

int perfect_num(int n, int m) {
    int cnt = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            for (int k = 1; k + i <= n && k + j <= m; ++k) {
                if (arr[i][k + j] == 0 || arr[k + i][j] == 0)
                    break;
                if (is_perfect(i, i + k, j, j + k)) {
                    ++cnt;
                }
            }
        }
    }
    return cnt;
}

int main() {
    int n, m;
    std::cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            std::cin >> arr[i][j];
            if (arr[i][j] == 0) arr[i][j] = -1;
        }
    }
    get_prefix(n, m);
    std::cout << perfect_num(n, m);
}
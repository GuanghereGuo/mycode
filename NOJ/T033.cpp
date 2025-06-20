#include <iostream>
#include <vector>

using namespace std;

int phiEuler(int n) {
    vector<int> phi(n + 1), prime;
    vector<bool> isSieved(n + 1, false); // 初始化筛数组
    int sum = 0;

    phi[1] = 1;

    for (int i = 2; i <= n; ++i) {
        if (!isSieved[i]) {
            prime.push_back(i); // 将素数加入prime数组
            phi[i] = i - 1;
        }
        for (size_t j = 0; j < prime.size() && i * prime[j] <= n; ++j) {
            int comp = i * prime[j];
            isSieved[comp] = true;
            if (i % prime[j] == 0) {
                phi[comp] = prime[j] * phi[i];
                break;
            } else {
                phi[comp] = (prime[j] - 1) * phi[i];
            }
        }
    }

    // 计算欧拉函数的和
    for (int i = 1; i <= n - 1; ++i) {
        sum += phi[i];
    }

    return sum;
}

int main() {
    int n;
    cin >> n;
    int result = n == 1 ? 0 : (2 * phiEuler(n) + 1);
    cout << result << endl;
    return 0;
}

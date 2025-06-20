#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Player {
    long long v; // 速度
    long long w; // 体重
};

// 检查是否可以让队伍的最慢速度达到 mid
bool canAchieveSpeed(long long mid, vector<Player>& players) {
    int n = players.size();
    vector<bool> used(n, false);  // 标记是否某个队员被背负
    // 尽量让较轻的队员被较重的队员背
    for (int i = n - 1; i >= 0; --i) {
        if (players[i].v >= mid) continue;  // 如果当前速度已经大于等于 mid，跳过
        bool found = false;
        for (int j = 0; j < i; ++j) {
            if (!used[j] && players[j].w >= players[i].w && players[j].v - (players[i].w - players[j].w) >= mid) {
                used[j] = true;
                found = true;
                break;
            }
        }
        if (!found) return false;
    }
    return true;
}

int main() {
    int T;
    cin >> T; // 读取测试组数
    while (T--) {
        int n;
        cin >> n; // 读取队员数量
        vector<Player> players(n);
        long long max_v = 0; // 记录最大速度的上限

        // 读取每个队员的速度和体重
        for (int i = 0; i < n; ++i) {
            cin >> players[i].v >> players[i].w;
            max_v = max(max_v, players[i].v); // 记录最大速度的上限
        }

        // 按照体重升序排列
        sort(players.begin(), players.end(), [](const Player& a, const Player& b) {
            return a.w < b.w;
        });

        // 二分答案，查找队伍的最大最慢速度
        long long left = 0, right = max_v;
        long long answer = 0;

        while (left <= right) {
            long long mid = (left + right) / 2;
            if (canAchieveSpeed(mid, players)) {
                answer = mid; // 如果当前 mid 可行，尝试更高的速度
                left = mid + 1;
            } else {
                right = mid - 1; // 否则，尝试更低的速度
            }
        }

        cout << answer << endl; // 输出结果
    }

    return 0;
}

#include <iostream>
#include <unordered_map>
#include <vector>

int main() {
    int n, m, s;
    std::cin >> n >> m >> s;

    std::vector<int> group_message_count(n + 1, 0);
    std::vector<std::unordered_map<int, int>> student_group_last_received(m + 1);
    std::vector<int> message_count(m + 1, 0);

    for (int i = 0; i < s; ++i) {
        int t, x, y;
        std::cin >> t >> x >> y;

        if (t == 1) {
            student_group_last_received[x][y] = group_message_count[y];
        } else if (t == 2) {
            message_count[x] += group_message_count[y] - student_group_last_received[x][y];
            student_group_last_received[x].erase(y);
        } else if (t == 3) {
            group_message_count[y]++;
            student_group_last_received[x][y]++;
        }
    }

    for (int student = 1; student <= m; ++student) {
        for (const auto& [group, last_received] : student_group_last_received[student]) {
            message_count[student] += group_message_count[group] - last_received;
        }
    }

    for (int i = 1; i <= m; ++i) {
        std::cout << message_count[i] << '\n';
    }
}
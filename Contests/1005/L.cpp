//
// Created by 24087 on 24-10-5.
//
#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

int main() {
    int n, m, q;
    cin >> n >> m >> q;

    vector<int> spicy_values(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> spicy_values[i];
    }

    vector<vector<int>> graph(n + 1);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    vector<pair<int, int>> tourists(q);
    for (int i = 0; i < q; ++i) {
        cin >> tourists[i].first >> tourists[i].second;
    }

    vector<vector<int>> distances(101, vector<int>(n + 1, INT_MAX));
    for (int spicy = 1; spicy <= 100; ++spicy) {
        queue<int> bfs_queue;
        for (int i = 1; i <= n; ++i) {
            if (spicy_values[i] <= spicy) {
                distances[spicy][i] = 0;
                bfs_queue.push(i);
            }
        }

        while (!bfs_queue.empty()) {
            int current = bfs_queue.front();
            bfs_queue.pop();

            for (int neighbor : graph[current]) {
                if (distances[spicy][neighbor] == INT_MAX) {
                    distances[spicy][neighbor] = distances[spicy][current] + 1;
                    bfs_queue.push(neighbor);
                }
            }
        }
    }

    for (const auto& tourist : tourists) {
        int start = tourist.first;
        int max_spicy = tourist.second;
        int min_distance = distances[max_spicy][start];
        if (min_distance == INT_MAX) {
            min_distance = -1;
        }
        cout << min_distance << '\n';
    }
}
#include <iostream>
#include <deque>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, k;
    std::cin >> n >> k;
    std::vector<int> vec(n + 1);
    std::deque<int> dq_max, dq_min;

    for(int i = 1; i <= n; i++) {
        std::cin >> vec[i];
    }
    for(int i = 1; i <= n; i++) {
        if(!dq_min.empty() && dq_min.front() + k <= i) {
            dq_min.pop_front();
        }
        while(!dq_min.empty() && vec[dq_min.back()] >= vec[i]) {
            dq_min.pop_back();
        }
        dq_min.push_back(i);
        if(i >= k) {
            std::cout << vec[dq_min.front()] << ' ';
        }
    }
    std::cout << '\n';
    for(int i = 1; i <= n; i++) {
        if(!dq_max.empty() && dq_max.front() + k <= i) {
            dq_max.pop_front();
        }
        while(!dq_max.empty() && vec[dq_max.back()] <= vec[i]) {
            dq_max.pop_back();
        }
        dq_max.push_back(i);
        if(i >= k) {
            std::cout << vec[dq_max.front()] << ' ';
        }
    }
}

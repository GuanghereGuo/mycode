//
// Created by 24087 on 24-10-16.
//
#include <iomanip>
#include <iostream>
#include <queue>
#include <vector>

class MedianFinder {
private:
    std::priority_queue<int> max_heap;
    std::priority_queue<int, std::vector<int>, std::greater<int>> min_heap;

public:
    void add_num(const int num) {
        max_heap.push(num);
        min_heap.push(max_heap.top());
        max_heap.pop();

        if (max_heap.size() < min_heap.size()) {
            max_heap.push(min_heap.top());
            min_heap.pop();
        }
    }

    [[nodiscard]] double find_median() const {
        if (max_heap.size() > min_heap.size()) {
            return max_heap.top();
        } else {
            return (max_heap.top() + min_heap.top()) / 2.0;
        }
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    std::vector<int> qu;
    int x;
    MedianFinder mf;
    do {
        std::cin >> x;
        if(x == 0) {
            for(int i = 0; i < qu.size(); ++i) {
                std::cout << qu[i] << " ";
            }
            std::cout << std::fixed << std::setprecision(6) <<  mf.find_median() << std::endl;
            continue;
        }
        qu.push_back(x);
        mf.add_num(x);
    }while(x >= 0);
}
//
// Created by 24087 on 24-10-5.
//
#include <iostream>
#include <queue>
#include <unordered_set>

struct State {
   private:
    unsigned long long data;
    unsigned depth;

   public:
    State(unsigned volume1, unsigned volume2, unsigned depth = 0)
        : data(static_cast<unsigned long long>(volume1) << 32 | volume2), depth(depth) {}
    [[nodiscard]] unsigned get_volume1() const { return data >> 32; }
    [[nodiscard]] unsigned get_volume2() const { return data & 0xffffffff; }
    [[nodiscard]] unsigned get_depth() const { return depth; }
    [[nodiscard]] unsigned long long get_data() const { return data; }
};

int main() {
    int volume1, volume2, target;
    std::cin >> volume1 >> volume2 >> target;

    std::queue<State> qu;
    std::unordered_set<unsigned long long> vis;

    qu.emplace(0, 0, 0);

    while (!qu.empty()) {
        auto now = qu.front();
        qu.pop();

        if (now.get_volume1() == target || now.get_volume2() == target) {
            std::cout << now.get_depth();
            return 0;
        }
        vis.insert(now.get_data());

        if (now.get_volume1() != volume1) {
            State newState(volume1, now.get_volume2(), now.get_depth() + 1);
            if (vis.find(newState.get_data()) == vis.end()) {
                qu.push(newState);
            }
        }
        if (now.get_volume2() != volume2) {
            State newState(now.get_volume1(), volume2, now.get_depth() + 1);
            if (vis.find(newState.get_data()) == vis.end()) {
                qu.push(newState);
            }
        }
        if (now.get_volume1() != 0) {
            State newState(0, now.get_volume2(), now.get_depth() + 1);
            if (vis.find(newState.get_data()) == vis.end()) {
                qu.push(newState);
            }
        }
        if (now.get_volume2() != 0) {
            State newState(now.get_volume1(), 0, now.get_depth() + 1);
            if (vis.find(newState.get_data()) == vis.end()) {
                qu.push(newState);
            }
        }
        if (now.get_volume1() != volume1 && now.get_volume2() != 0) {// Pour from 2 to 1
            const unsigned pour =
                std::min(volume1 - now.get_volume1(), now.get_volume2());
            State newState(now.get_volume1() + pour, now.get_volume2() - pour,
                           now.get_depth() + 1);
            if (vis.find(newState.get_data()) == vis.end()) {
                qu.push(newState);
            }
        }
        if (now.get_volume2() != volume2 && now.get_volume1() != 0) {// Pour from 1 to 2
            const unsigned pour =
                std::min(volume2 - now.get_volume2(), now.get_volume1());
            State newState(now.get_volume1() - pour, now.get_volume2() + pour,
                           now.get_depth() + 1);
            if (vis.find(newState.get_data()) == vis.end()) {
                qu.push(newState);
            }
        }
    }
    std::cerr << "ERROR: No solution found!";
}
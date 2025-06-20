#include <bitset>
#include <iostream>
#include <map>
#include <unordered_set>

constexpr int mod = 1e9 + 7;

int main() {
    freopen("../text.in", "w", stdout);
    srand(time(0));
    int n = 300;
    std::cout << n << '\n';
    std::unordered_set<int> st;
    while(st.size() <= n) {
        st.insert(static_cast<int>(rand() * 114514.1919810) % static_cast<int>(1e9 + 7));
    }
    for(int i : st) {
        std::cout << i << ' ';
    }
}

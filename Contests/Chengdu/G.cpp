//
// Created by 24087 on 24-10-31.
//
#include <iostream>
#include <unordered_set>
#include <set>

int main() {
    std::ios::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);

    int n, x, y;
    std::cin >> n >> y;
    std::unordered_set<int> st;

    st.insert(0);

    for(int i = 2; i <= n; i++) {
        x = y;
        std::cin >> y;
        st.insert(x);
        st.insert(y);
        st.insert(x & y);
        st.insert(x | y);
        st.insert(x ^ y);
        st.insert(x & ~y);
        st.insert(~x & y);
    }
    std::cout << st.size();
}
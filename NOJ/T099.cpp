//
// Created by 24087 on 24-10-9.
//
#include <iostream>
#include <unordered_set>

int main() {
    int n;
    std::cin >> n;
    std::unordered_set<int> st;
    int ans = 0;
    for(int i = 1, x; i <= n; i++) {
        std::cin >> x;
        if(st.find(x) != st.end()) {
            ans++;
        } else {
            st.insert(x);
        }
    }
    std::cout << ans;
}
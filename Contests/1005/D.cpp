//
// Created by 24087 on 24-10-5.
//
#include <iostream>

auto attack(int &x, int &y) -> long long {
    long long ret = 0;
    if(x >= y) {
        ret = y;
        x -= y;
        y = 0;
    } else {
        ret = x;
        y -= x;
        x = 0;
    }
    return ret;
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int t;
    std::cin >> t;

    while(t--) {
        int a, b, c, d, e, f;
        std::cin >> a >> b >> c
                 >> d >> e >> f;
        //石头 布 剪刀
        long long ans = 0;
        ans += attack(e ,a);
        ans += attack(f ,b);
        ans += attack(d ,c);
        attack(d, a);
        attack(e, b);
        attack(f, c);
        ans -= attack(a, f);
        ans -= attack(b, d);
        ans -= attack(c, e);
        std::cout << ans << '\n';
    }

}
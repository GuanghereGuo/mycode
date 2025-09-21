//
// Created by guanghere on 2025/9/21.
//
#include <bits/stdc++.h>
using namespace std;

using pii = std::pair<int, int>;
inline bool between(int l, int r, int x) {
    return (l <= x && x <= r) || (r <= x && x <= l);
}
inline int sign(int x) {
    if (x >= 0) return 1;
    if (x < 0) return -1;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    pii s, t, p,vec;
    vector<pii> ans;
    std::cin >> s.first >> s.second >> t.first >> t.second;
    std::cin >> p.first >> p.second;

    vec.first=sign(t.first-s.first);
    vec.second=sign(t.second-s.second);

    if (between(s.first,t.first,p.first)&&between(s.second,t.second,p.second)){
        if (vec.first>0) {
            ans.push_back(pii(-1e5,s.second));
            ans.push_back(pii(-1e5,vec.second*1e5));
            ans.push_back(pii(t.first,vec.second*1e5));
        }else {
            ans.push_back(pii(1e5,s.second));
            ans.push_back(pii(1e5,vec.second*1e5));
            ans.push_back(pii(t.first,vec.second*1e5));
        }
    }else if(!between(s.first,t.first,p.first)) {
        ans.push_back(pii(sign(s.first-t.first)*-1e5,s.second));
        ans.push_back(pii(sign(s.first-t.first)*-1e5,t.second));
    }else {
        ans.push_back(pii(s.first,sign(s.second-t.second)*-1e5));
        ans.push_back(pii(t.first,sign(s.second-t.second)*-1e5));
    }
    cout << ans.size() << '\n';
    for (auto &i:ans)cout << i.first << ' ' << i.second << '\n';
}

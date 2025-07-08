//
// Created by guanghere on 25-7-8.
//
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
#define int long long

signed main() {
#ifdef DEBUG
    freopen("1.in","r",stdin);
    freopen("1.out","w",stdout);
#endif
    // std::ios::sync_with_stdio(false);
    // std::cin.tie(nullptr);
    // std::cout.tie(nullptr);

    int n, m, k;
    std::cin >> n >> m;

    std::vector<int> a(n + 1), pb,pl;
    std::vector<std::pair<int, int>> q(m + 1);

    // Read input values
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i];
    }
    std::cin >> k;
    for (int i = 1; i <= m; i++) {
        std::cin >> q[i].first >> q[i].second;
    }

    //init period
    int start = 1;
    for (int i = 2; i <= n; i++) {
        if (a[i] > a[i - 1]) {
            continue;
        }
        pb.push_back(start);
        pl.push_back(i - 1);
        start = i;
    }
    if (start != n) {
        pb.push_back(start);
        pl.push_back(n);
    }
    vector<int> sum(pb.size() + 1, 0);
    // Calculate prefix sums for periods
    for (int i = 0; i < pb.size(); i++) {
        sum[i + 1] = sum[i] + a[pl[i]] - a[pb[i]];
    }
    // Process each query
    for (int i = 1; i <= m; i++) {
        int first = std::lower_bound(pl.begin(), pl.end(), q[i].first) - pl.begin();
        int last = std::upper_bound(pb.begin(), pb.end(), q[i].second) - pb.begin() - 1;
        int ans = k;
        if(first==last)ans+=a[q[i].second] - a[q[i].first];
        else{
            ans += a[pl[first]] - a[q[i].first];
            ans += a[q[i].second] - a[pb[last]];
            if(last-first>=2)ans+= sum[last] - sum[first+1];
        }
#ifdef DEBUG
        cout<<a[pl[first]] - a[q[i].first]<<" "<< a[q[i].second] - a[pb[last]]<<" "<<sum[last] - sum[first]<<" "<<last<<" "<<first<<endl;
#endif
        std::cout << ans << '\n';
    }
}
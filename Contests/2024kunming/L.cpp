//
// Created by guanghere on 2025/10/12.
//
#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n,m,x,cnt=0,cnt1;
    cin >> n >> m;
    vector<int> a,b;
    for (int i=0;i<n;i++){
        cin >> x;
        a.push_back(x);
        a[i]--;
        cnt+=(bool)a[i];
    }
    if (cnt!=n)cnt++;
    // cout<<cnt<<endl;
    for (int i=0;i<m;i++) {
        cin >> x;
        b.push_back(x);
    }
    sort(a.begin(),a.end());
    sort(b.begin(),b.end());
    while (cnt--) {
        b[m-1]--;
        sort(b.begin(),b.end());
    }
    int cura=0,curb=0,cnt1_=0;cnt1=0;
    for (;cura<n;cura++,cnt1++) if (a[cura]) break;
    for (;curb<m;curb++,cnt1++) if (b[curb]>0) break;
    while (1) {
    cout<<" "<<cnt1<<" "<<cura<<" "<<curb<<endl;
        cnt1_=cnt1;
        for (;cura<n;cura++,cnt1++) if (a[cura]>cnt1_) break;
        for (;curb<m;curb++,cnt1++) if (b[curb]>cnt1_) break;
        if (cnt1==cnt1_) break;
    }
    cout<<curb<<endl;
    if (curb==m) cout << "YES\n";
    else cout << "NO\n";
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }
}
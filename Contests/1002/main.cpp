#include<bits/stdc++.h>

using namespace std;   const int N = 200;

mt19937 rnd(chrono::system_clock::now().time_since_epoch().count());

int main(){
    cout << 1 << '\n' << 20 << '\n';
    for(int i = 1; i <= 20; i++) cout << rnd() % 10 + 1 << ' ';
    return 0;
}
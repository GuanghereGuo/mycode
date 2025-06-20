//I C++20 WZH
#include <iostream>
#include <string>
using namespace std;
string s;
int T;
int main() {
    cin>>T;
    while (T--) {
        s.clear();
        cin>>s;
        //统计连续
        int lassame=s.size()-1,ans=0,evenexist=0,tmpans=1,pl=1;
        while(s[lassame]==s[0]&&lassame!=0) {
            tmpans++;
            lassame--;
        }
        while (s[0]==s[pl]&&pl<=lassame) {
            tmpans++;
            pl++;
        }
        ans+=tmpans/2;
        if(tmpans==s.size()) {
            cout<<tmpans/2<<endl;
            continue;
        }
        if(!(tmpans%2))evenexist=1;
        //正扫
        int now=0;
        for(;pl<=lassame;pl=now) {
            now=pl+1;
            tmpans=1;
            while(s[pl]==s[now]&&now<=lassame) {
                tmpans++;
                now++;
            }
            ans+=tmpans/2;
            if(!(tmpans%2))evenexist=1;
        }
        cout<<ans+(evenexist==1?-1:0)<<endl;
    }
}
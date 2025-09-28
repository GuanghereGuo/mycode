#include<bits/stdc++.h>
using namespace std;

int n,s,ans,cur;
int s2,s1,ss1;
int a[(int)3e5];
int main(){
    cin>>n>>s;
    s--;
    for(int i=0;i<n;i++)cin>>a[i];
    sort(a,a+n);
    for(ans=0;ans<n;ans++){
        if(cur>=s)break;
        switch(a[ans]%3){
            case 0:
                cur+=a[ans]/3;
                break;
            case 1:
                if(s2){
                    cur+=a[ans]/3;
                    s2--;
                    break;
                }
                if(s1){
                    cur+=a[ans]/3;
                    s1--;
                    ss1++;
                    break;
                }
                cur+=a[ans]/3+1;
                s1++;
                break;
            case 2:
                if(s1){
                    cur+=a[ans]/3;
                    s1--;
                    break;
                }
                if(ss1)ss1--,s1++;
                else s2++;
                cur+=a[ans]/3+1;
                break;
        }
        //		cout<<a[ans]<<" "<<cur<<endl;
    }
    if(ans!=n)ans++;
    cout<<ans;
}
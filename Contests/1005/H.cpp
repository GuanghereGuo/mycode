//
// Created by 24087 on 24-10-5.
//
// Problem H by HuangZiheng
#include<iostream>
#include<string>
using namespace std;
string s;
int T;
int main() {
    cin>>T;
    while(T--) {
        cin>>s;
        char op=s[s.size()-6];
        if(s=="ikimasu") {
            cout<<"itte"<<endl;
        }else if(op=='h'&&s[s.size()-7]=='c') {
            cout<<s.substr(0,s.size()-7)+"tte"<<endl;
        }else if(op=='r') {
            cout<<s.substr(0,s.size()-6)+"tte"<<endl;
        }else if(op=='b'||op=='m'||op=='n') {
            cout<<s.substr(0,s.size()-6)+"nde"<<endl;
        }else if(op=='k') {
            cout<<s.substr(0,s.size()-6)+"ite"<<endl;
        }else if(op=='g') {
            cout<<s.substr(0,s.size()-6)+"ide"<<endl;
        }else if(op=='h'&&s[s.size()-7]=='s') {
            cout<<s.substr(0,s.size()-7)+"shite"<<endl;
        }
    }
    return 0;
}
#include<stdio.h>
#include<string.h>
int main(){
    char A[1000],a[1000];
    gets(A);
    gets(a);
    int i=strlen(A);
    int j=strlen(a);
    int m=j;
    for(int k=0;k<m;k++){
        if(A[i-1]==a[j-1]){
            i--;
            j--;
            continue;
        }
        else break;
    }
    if(j==0) printf("Yes");
    else printf("No");
    return 0;
}


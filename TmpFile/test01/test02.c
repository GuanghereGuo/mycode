#include<stdio.h>
int main()
{
    int x;
    scanf("%d",&x);
    if (x < 0 || x > 100) {
        printf("ERROR");
        return 0;
    }
    x/=10;
    switch (x) {
        case 10:
        case 9:
            printf("A");
        break;
        case 8:
            printf("B");
        break;
        case 7:
            printf("C");
        break;
        case 6:
            printf("D");
        break;
        case 5:
        case 4:
        case 3:
        case 2:
        case 1:
        case 0:
            printf("E");
        break;
        default:
            printf("ERROR");
        break;
    }
    return 0;
}
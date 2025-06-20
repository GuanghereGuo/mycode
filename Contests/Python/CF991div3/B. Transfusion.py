import math

t = int(input())
for i in range(t):
    n = int(input())
    arr = list(map(int, input().split()))
    sum_odd = sum(arr[::2])
    sum_even = sum(arr[1::2])
    if sum_odd % math.ceil(n / 2) != 0 or \
            sum_even % math.floor(n / 2) != 0 or \
            sum_odd // math.ceil(n / 2) != sum_even // math.floor(n / 2):
        print("NO")
    else:
        print("YES")
t = int(input())
for i in range(t):
    n, m = map(int, input().split())
    cnt = 0
    ans = n
    for j in range(n):
        cnt += len(input())
        if cnt > m and ans == n:
            ans = j
    print(ans)
t = int(input())

for _ in range(t):
    n, k = map(int, input().split())
    s = input().strip()
    num = s.count("nanjing")
    for i in range(min(7, k)):
        s = s[1:] + s[0]
        num = max(num, s.count("nanjing"))
    print(num)
t = int(input())

for _ in range(t):
    n, a = map(int, input().split())
    s = input()
    if a * "1" in s or (a + 1) * "0" in s:
      print(len(s))
    else:
      print(s.count("1"))
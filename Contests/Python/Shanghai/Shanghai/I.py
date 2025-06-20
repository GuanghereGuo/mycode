from queue import PriorityQueue
import sys

t = int(input())
MOD = 998244353

for i in range(t):
    n, k = map(int, input().split())
    vals = list(filter(lambda x: x != 0, map(int, input().split())))

    if len(vals) == 0:
        print(0)
        continue

    vals.sort()
    while len(vals) >= k:
        product = 1
        for j in range(k):
            product *= vals.pop()
            product %= MOD
        vals.append(product % MOD)
    print(vals[-1] % MOD)

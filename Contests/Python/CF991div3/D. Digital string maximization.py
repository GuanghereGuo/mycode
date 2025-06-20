def circle(s, begin, end):
    pass

def solve():
    #s = np.array(list(map(int, input())), dtype=np.int8)
    s = list(map(int, input()))
    #n = s.size
    n = len(s)
    for i in range(0, n):
        max_n = s[i]
        max_idx = i
        for j in range(i + 1, min(n, i + 10)):
            if s[j] - (j - i) > max_n:
                max_n = s[j] - (j - i)
                max_idx = j
        if max_idx != i:
            s[i:max_idx + 1] = [s[max_idx] - (max_idx - i)] +  s[i:max_idx]
    print(''.join(map(str, s)))

t = int(input())
for _ in range(t):
    solve()
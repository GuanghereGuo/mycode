n = int(input())

for _ in range(n):
    s = input()
    alpha, digit, other = False, False, False
    for c in s:
        if alpha and digit and other:
            break
        if c.isalpha():
            alpha = True
        elif c.isdigit():
            digit = True
        else:
            other = True
    if alpha and digit and other:
        d = {}
        for c in s:
            d[c] = d.get(c, 0) + 1
        if max(d.values()) >= 3:
            print(1)
        else:
            print(2)
    else:
        print(0)


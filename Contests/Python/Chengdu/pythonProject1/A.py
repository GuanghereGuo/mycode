t = int(input())

for i in range(t):
    s = input()
    if s[0] != ">" or s[-3:] != ">>>" or s.count("-") == 0:
        print("No")
    else:
        print("Yes %d\n1 %d" % (s.count(">") - 3, len(s)))
        j = 0
        for j in range(len(s) - 4, -1, -1):
            if s[j] == "-":
                break
            print("1 %d" % (j + 3))
        for i in range(1, j):
            if s[i] == ">":
                print("%d %d" % (i + 1, j + 4 - i))

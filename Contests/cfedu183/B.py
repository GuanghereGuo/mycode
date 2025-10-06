t = int(input())
for _ in range(t):
    n, k = map(int, input().split())
    s = input()
    zero = s.count("0")
    one = s.count("1")
    two = s.count("2")
    ans = zero * "-"
    if n == k:
        print(n * "-")
        continue
    if 2 * two + one + zero <= n:
        cnt = n - (2 * two + one + zero)
        ans += "?" * two + cnt * "+" + "?" * two + "-" * one
    else:
        ans += (n - one - zero) * "?" + "-" * one
    print(ans)

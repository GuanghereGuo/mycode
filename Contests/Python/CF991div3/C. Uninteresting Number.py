def check(max_x, max_y, c):# 2x + 6y == c mod 9
    for x in range(min(9, max_x + 1)):
        for y in range(min(3, max_y + 1)):
            if (2 * x + 6 * y) % 9 == c:
                return True
    return False

t = int(input())
for _ in range(t):
    arr = list(map(int, input()))
    remainder = 9 - sum(arr) % 9
    if remainder == 9:
        print("YES")
        continue
    num_of_2 = arr.count(2) #提供2的贡献
    num_of_3 = arr.count(3) #提供6的贡献
    #print(num_of_2, num_of_3, remainder)
    if check(num_of_2, num_of_3, remainder):
        print("YES")
    else:
        print("NO")


n, m = map(int, input().split())
things = {}
for i in range(m):
    ll = list(input().split())
    cost = int(ll[1])
    num = int(ll[2])
    things[ll[0]] = [cost, num]

sum = 0
for i in range(n):
    nn = list(input().split())
    for j in range(3):
        if things[nn[j]][1] > 0:
            things[nn[j]][1] = things[nn[j]][1] - 1
            sum += things[nn[j]][0]

print(sum)
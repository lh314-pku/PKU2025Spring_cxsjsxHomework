N, M = map(int, input().split())
lights = []
for i in range(N):
    lights.append(0)

for j in range(M):
    for i in range(N):
        if (i + 1) % (j + 1) == 0:
            if lights[i] == 0:
                lights[i] = 1
            else:
                lights[i] = 0

output = False
for i in range(N):
    if lights[i] != 0:
        if output:
            print(",", end="")
        print(i + 1, end="")
        output = True
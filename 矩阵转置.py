n, m = map(int, input().split())
matrix = []
for i in range(n):
    line = list(map(int, input().split()))
    matrix.append(line)

for j in range(m):
    for i in range(n):
        if i == n - 1:
            print(matrix[i][j])
        else:
            print(matrix[i][j], end=" ")
    
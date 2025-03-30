def min_sum(N):
    M = N * (-1) + 1
    k = 1
    for i in range(N):
        k = k * N
    M = M + k
    return M

n = int(input())
print(min_sum(n))
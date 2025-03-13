n = int(input())
k = int(pow(n, 0.5))
min_length = 0
for i in range(k):
    if n % (i + 1) == 0:
        min_length = (i + 1 + n // (i + 1)) * 2
print(min_length)
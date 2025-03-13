x, y, n = input().split()
x = int(x)
y = int(y)
if n == '+':
    print(x + y)
elif n == '-':
    print(x - y)
elif n == '*':
    print(x * y)
elif n == '/':
    if y == 0:
        print("Divided by zero!")
    else:
        print(x // y)
else:
    print("Invalid operator!")
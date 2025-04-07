def mysum(x):
# 在此处补充你的代码
# 高阶函数（知识点）
    def inner_sum(y=None):
        if y is None:  # 如果没有传入参数，则计算当前累加结果
            return x
        return mysum(x + y)  # 累加并返回一个新的函数
    return inner_sum

def exec(g,i) : #call g for i times
    if i == 1 :
        g()
    else:
        g()
        exec(g,i-1)

k = mysum(1)(2)(3)(4)
k2 = mysum(10)(20)

print(k())
print(k2())

while True:
    try:
        s = input()
        s = s.split()
        k = mysum
        for x in s:
            k = k(int(x))
        exec(k,int(s[0]))
        print(k())
    except:  #读到 eof产生异常
        break
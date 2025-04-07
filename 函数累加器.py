#pylint: disable = no-value-for-parameter
def accfunc(f):
# 在此处补充你的代码
# 知识点：函数工厂
    def inner_acc(new_f=None):
        if new_f is None:  # 如果没有传入新的函数，则表示执行累积的操作
            def combined_func(x):
                result = x
                for func in inner_acc.funcs:  # 依次调用累积的函数
                    result = func(result)
                return result
            return combined_func
        else:
            inner_acc.funcs.append(new_f)  # 将新的函数添加到列表中
            return inner_acc
    inner_acc.funcs = [f]  # 初始化时保存第一个函数
    return inner_acc
def f1(x):
    return x + 1
def f2(x):
    return x * x
def f3(x):
    return x + x
def f4(x):
    return x*3
def f5(x):
    return x-4

while True:
    try:
        s = input()
        n = int(input())
        s = s.split()
        k = accfunc
        for x in s:
            k = k(eval(x))
        print(k()(n))
    except:  #读到 eof产生异常
        break
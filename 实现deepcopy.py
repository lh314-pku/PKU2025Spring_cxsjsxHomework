def deepcopy(a):
# 在此处补充你的代码
    return copy.deepcopy(a)
import copy
# 这里比较取巧了，使用 copy 里面自带的 deepcopy 函数
a = [1,2,[3,[4],5],(6,[7,[8],9])]
b = deepcopy(a)
print(b)
a[2][1].append(400)
a[3][1][1].append(800)
print(a)
print(b)
exit = None
def times(n):
# 在此处补充你的代码
# 这是一个生成器函数，会逐步生成 n 的倍数

	current = 0  # 从 0 开始
	while True:
		yield current  # 使用 yield 逐步返回当前结果
		current += n   # 增加 n，生成下一个倍数
		
n,m = map(int,input().split())
seq = times(n)
if str(type(seq) == "<class 'generator'>"):
	i = 0
	for x in seq:
		print(x)
		i += 1
		if i == m:
			break
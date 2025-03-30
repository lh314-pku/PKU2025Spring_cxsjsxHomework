class A:
	def __init__(self,x):
		self.x = x
# 在此处补充你的代码
	def __lt__(self, other):
		if isinstance(other, A):
			return self.x < other.x
		else:
			return self.x < other
	# greater or equal 相当于重载 '>='
	def __ge__(self, other):
		if isinstance(other, A):
			return self.x >= other.x
		else:
			return NotImplemented
a,b,c = map(int,input().split())
print(isinstance(A(2),A))
print(A(a) < A(b))
print(A(a) >= A(c))
print(A(a) < c)
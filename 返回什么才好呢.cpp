#include <iostream>
using namespace std;
class A {
public:
	int val;

	A(int /*由此复制*/x) {
		val = x;
	}
	A() {
		val = 123;
	}
	// 重载构造函数
	// 分别对应 第30，32行 和 第27行（默认val = 123

	A& GetObj() {
		return *this;
	}
	// 'm' 和 'A(n)' 都是（经过类型转化）的 A 的实例
	// GetObj函数只要接受并返回引用
	// 修改对应的 val 值
	// 在此处补充你的代码
};
int main()
{
	int m, n;
	A a;
	cout << a.val << endl;
	while (cin >> m >> n) {
		a.GetObj() = m;
		cout << a.val << endl;
		a.GetObj() = A(n);
		cout << a.val << endl;
	}
	return 0;
}
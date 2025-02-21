#include <iostream>
#include <string>
using namespace std;

class Base {
public:
	int k;
	Base(int n) :k(n) { }
};

class Big
{
public:
	int v;
	Base b;
	// 在此处补充你的代码
	Big(int x) :v(x), b(x){}
};
// Base 是 Big 的内部类，不能简单定义构造函数
// 当出现 自定义类型成员 时，应该使用 初始化列表

int main()
{
	int n;
	while (cin >> n) {
		Big a1(n);
		Big a2 = a1;
		cout << a1.v << "," << a1.b.k << endl;
		cout << a2.v << "," << a2.b.k << endl;
	}
}
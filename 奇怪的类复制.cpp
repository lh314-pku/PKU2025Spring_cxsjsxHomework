#include <iostream>
using namespace std;
class Sample {
public:
	int v;
	// 在此处补充你的代码
	Sample(int x) {
		v = x;
	} // （1）
	Sample(const Sample& a) {
		v = a.v + 2;
	} // （2）
	Sample() {
		v = 0;
	} // （3）
	// 不要问，问就是神奇的类复制问题（
	// 其实就是调用（2）构造函数时会加2
	// 以及 PrintAndDouble 函数用于生成临时变量也会调用（2）
	// 故 b+4，c+2
};
void PrintAndDouble(Sample o)
{
	cout << o.v;
	cout << endl;
}
int main()
{
	Sample a(5);
	Sample b = a;
	PrintAndDouble(b);
	Sample c = 20;
	PrintAndDouble(c);
	Sample d;
	d = a;
	cout << d.v;
	return 0;
}
#include <iostream> 
using namespace std;
class MyInt
{
	int nVal;
public:
	MyInt(int n) { nVal = n; }
	// 在此处补充你的代码
	friend MyInt& operator- (MyInt &ii, const int n) {
		ii.nVal -= n;
		return ii;
	}// 重载'-'

	operator int() {
		return nVal;
	}// 重载 'int()' 作为强制类型转换
	// 如果需要显式的类型转换，需要加'explicit'关键词
};
int Inc(int n) {
	return n + 1;
}
int main() {
	int n;
	while (cin >> n) {
		MyInt objInt(n);
		objInt - 2 - 1 - 3;
		cout << Inc(objInt);
		cout << ",";
		objInt - 2 - 1;
		cout << Inc(objInt) << endl;
	}
	return 0;
}
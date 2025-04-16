#include <iostream>
#include <string>
using namespace std;
// 在此处补充你的代码
template <class T,typename Func>
void MyForeach(T* begin, T* end, Func func){
    while (begin != end) {// 遍历数组
        func(*begin);
        ++begin;          // 移动到下一个元素
    }
}
void Print(string s)
{
	cout << s;
}
void Inc(int & n)
{
	++ n;
}
string array[100] = {" "};
int a[100];
int main() {
	int m,n;
	while(cin >> m >> n) {
		for(int i = 0;i < m; ++i)
			cin >> array[i];
		for(int j = 0; j < n; ++j)
			cin >> a[j];
		MyForeach(array,array+m,Print);		 
		cout << endl;
		MyForeach(a,a+n,Inc);		 
		for(int i = 0;i < n; ++i)
			cout << a[i] << ",";
		cout << endl;
	}
	return 0;
}
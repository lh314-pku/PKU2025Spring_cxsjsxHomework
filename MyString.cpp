#define _CRT_SECURE_NO_WARNINGS
// 避免 strcpy() 函数在 VS 中发生 C4996 报错
#include <iostream>
#include <string>
#include <cstring>
using namespace std;
class MyString {
	char* p;
public:
	MyString(const char* s) {
		if (s) {
			p = new char[strlen(s) + 1];
			strcpy(p, s);
		}
		else
			p = NULL;

	}
	~MyString() { if (p) delete[] p; }
	// 在此处补充你的代码

	void Copy(const char* s) {
		if (s) {
			p = new char[strlen(s) + 1];
			strcpy(p, s);
		}
		else
			p = NULL;
	}

	MyString& operator= (const MyString &str) {
		this->p = new char[strlen(str.p) + 1];
		// 动态分配内存
		// '+1' 是因为C风格字符串以'\n'结尾

		strcpy(p, str.p);
		// 赋值
		return *this;
	} // 复制构造函数1 重载'='
	  // MyString -> MyString

	MyString& operator= (const char *s) {
		this->p = new char[strlen(s) + 1];
		// 动态分配内存
		// '+1' 是因为C风格字符串以'\n'结尾

		strcpy(p, s);
		// 赋值
		return *this;
	} // 复制构造函数2 重载'='
	  // char * -> MyString

	friend ostream& operator<<(ostream& o, const MyString& str) {
		o << &str.p[0];
		return o;
	}// 友元函数，重载 '<<' 运算符
};
int main()
{
	char w1[200], w2[100];
	while (cin >> w1 >> w2) {
		MyString s1(w1), s2 = s1;
		MyString s3(NULL);
		s3.Copy(w1);
		cout << s1 << "," << s2 << "," << s3 << endl;

		s2 = w2;
		s3 = s2;
		s1 = s3;
		cout << s1 << "," << s2 << "," << s3 << endl;

	}
}
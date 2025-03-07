﻿#include <iostream> 
using namespace std;
class Point {
private:
	int x;
	int y;
public:
	Point() { };
	// 在此处补充你的代码
	friend istream& operator>> (istream& is, Point &p) {
		is >> p.x >> p.y;
		return is;
	}
	friend ostream& operator<< (ostream& os, const Point p) {
		os << p.x << ',' << p.y;
		return os;
	}
	// 非常简单的重载 '<<' 和 '>>' 运算符
};
int main()
{
	Point p;
	while (cin >> p) {
		cout << p << endl;
	}
	return 0;
}
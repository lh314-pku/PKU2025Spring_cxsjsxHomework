#include <iostream>
#include <string>
#include <list>
using namespace std;

class A{
private:
	string name;
public:
	A(string n) :name(n){}
	friend bool operator < (const class A& a1, const class A &a2);
	friend bool operator == (const class A &a1, const class A &a2){
		if (a1.name.size() == a2.name.size())
			return true;
		else
			return false;
	}
	friend ostream & operator << (ostream &o, const A &a){
		o << a.name;
		return o;
	}
	string get_name() const{
		return name;
	}
	int get_size() const{
		return name.size();
	}
};
// 在此处补充你的代码
bool operator<(const class A& a1, const class A& a2) {
	return (a1.get_size() < a2.get_size());
}
// **Show 函数模板**
template <typename T1, typename T2, typename T3>
void Show(T1 begin, T2 end, T3 operation) {
    for (auto it = begin; it != end; ++it) {
        operation(*it);
        if (next(it) != end) // 控制输出的空格
            cout << " ";
    }
}
// **辅助类：Print（用于打印字符串）**
class Print {
public:
    void operator()(const A &a) const {
        cout << a;
    }
};
// **排序仿函数：MyLarge**
template <class T>
class MyLarge {
public:
    bool operator()(const T &a1, const T &a2) const {
        return a1.get_name()[0] < a2.get_name()[0]; // 按首字母 ASCII 排序
    }
};

int main()
{
	list<A> lst;
	int ncase, n, i = 1;
	string s;
	cin >> ncase;
	while (ncase--){
		cout << "Case: "<<i++ << endl;
		cin >> n;
		for (int i = 0; i < n; i++){
			cin >> s;
			lst.push_back(A(s));
		}
		lst.sort();
		Show(lst.begin(), lst.end(), Print());

		cout << endl;
		lst.sort(MyLarge<A>());
		Show(lst.begin(), lst.end(), Print());
		cout << endl;
		lst.clear();

	}
	return 0;
}
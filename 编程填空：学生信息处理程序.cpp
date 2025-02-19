#include <iostream>
#include <string>
#include <cstdio>
#include <cstring>
#include <sstream>
#include <cstdlib>
using namespace std;

class Student {
	// 在此处补充你的代码
private:
	string name;
	int age;
	int num;
	int average_grade;
	int grades[4];
public:
	void input() {
		getline(cin, name, ',');
		char ch;
		cin >> age >> ch >> num;
		int a = 0;
		for (int i = 0; i < 4; i++) {
			cin >> ch >> a;
			grades[i] = a;
		}
	}

	void calculate() {
		int sum = 0;
		for (int i = 0; i < 4; i++) {
			sum += grades[i];
		}
		average_grade = sum / 4;
	}

	void output() {
		cout << name << ',' << age << ',' << num << ',' << average_grade;

	}
};

int main() {
	Student student;        // 定义类的对象
	student.input();        // 输入数据
	student.calculate();    // 计算平均成绩
	student.output();       // 输出数据
}
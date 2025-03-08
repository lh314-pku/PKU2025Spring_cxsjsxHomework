#define _CRT_SECURE_NO_WARNINGS
// 避免 strcpy() 函数在 VS 中发生 C4996 报错
#include <cstdlib>
#include <iostream>
using namespace std;
//int strlen(const char* s)
//{
//	int i = 0;
//	for (; s[i]; ++i);
//	return i;
//}
//void strcpy(char* d, const char* s)
//{
//	int i = 0;
//	for (i = 0; s[i]; ++i)
//		d[i] = s[i];
//	d[i] = 0;
//
//}
//int strcmp(const char* s1, const char* s2)
//{
//	for (int i = 0; s1[i] && s2[i]; ++i) {
//		if (s1[i] < s2[i])
//			return -1;
//		else if (s1[i] > s2[i])
//			return 1;
//	}
//	return 0;
//}
//void strcat(char* d, const char* s)
//{
//	int len = strlen(d);
//	strcpy(d + len, s);
//}
class MyString
{
private:
    char* data;
public:
    // 默认构造函数
    MyString() : data(new char[1]) { data[0] = '\0'; }

    // 构造函数（字符串初始化）
    MyString(const char* s) {
        data = new char[strlen(s) + 1];
        strcpy(data, s);
    }

    // 拷贝构造函数
    MyString(const MyString& other) {
        data = new char[strlen(other.data) + 1];
        strcpy(data, other.data);
    }

    // 析构函数
    ~MyString() {
        delete[] data;
    }

    // 赋值运算符（对象赋值）
    MyString& operator=(const MyString& other) {
        if (this == &other) return *this; // 防止自赋值
        delete[] data;
        data = new char[strlen(other.data) + 1];
        strcpy(data, other.data);
        return *this;
    }

    // 赋值运算符（C风格字符串赋值）
    MyString& operator=(const char* s) {
        delete[] data;
        data = new char[strlen(s) + 1];
        strcpy(data, s);
        return *this;
    }

    // 拼接运算符 +
    MyString operator+(const MyString& other) const {
        int len1 = strlen(data);
        int len2 = strlen(other.data);
        char* newData = new char[len1 + len2 + 1];
        strcpy(newData, data);
        strcat(newData, other.data);
        MyString result(newData);
        delete[] newData;
        return result;
    }

    // 拼接运算符 +=
    MyString& operator+=(const MyString& other) {
        int len1 = strlen(data);
        int len2 = strlen(other.data);
        char* newData = new char[len1 + len2 + 1];
        strcpy(newData, data);
        strcat(newData, other.data);
        delete[] data;
        data = newData;
        return *this;
    }

    // 比较运算符 ==
    bool operator==(const MyString& other) const {
        return strcmp(data, other.data) == 0;
    }

    // 比较运算符 <
    bool operator<(const MyString& other) const {
        return strcmp(data, other.data) < 0;
    }

    // 比较运算符 >
    bool operator>(const MyString& other) const {
        return strcmp(data, other.data) > 0;
    }

    // 下标运算符
    char& operator[](int index) {
        return data[index];
    }

    // 友元函数：输出流操作符 <<
    friend ostream& operator<<(ostream& os, const MyString& str) {
        os << str.data;
        return os;
    }

    // 截取子串
    MyString operator()(int start, int length) {
        char* newData = new char[length + 1];
        for (int i = 0; i < length && data[start + i] != '\0'; i++) {
            newData[i] = data[start + i];
        }
        newData[length] = '\0';
        MyString result(newData);
        delete[] newData;
        return result;
    }

    friend MyString operator+(const char* lhs, const MyString& rhs) {
        MyString temp(lhs);
        temp += rhs;  // 复用 += 运算符
        return temp;
    }
};

int CompareString(const void* e1, const void* e2)
{
	MyString* s1 = (MyString*)e1;
	MyString* s2 = (MyString*)e2;
	if (*s1 < *s2)
		return -1;
	else if (*s1 == *s2)
		return 0;
	else if (*s1 > *s2)
		return 1;
}
int main()
{
	MyString s1("abcd-"), s2, s3("efgh-"), s4(s1);
	MyString SArray[4] = { "big","me","about","take" };
	cout << "1. " << s1 << s2 << s3 << s4 << endl;
	s4 = s3;
	s3 = s1 + s3;
	cout << "2. " << s1 << endl;
	cout << "3. " << s2 << endl;
	cout << "4. " << s3 << endl;
	cout << "5. " << s4 << endl;
	cout << "6. " << s1[2] << endl;
	s2 = s1;
	s1 = "ijkl-";
	s1[2] = 'A';
	cout << "7. " << s2 << endl;
	cout << "8. " << s1 << endl;
	s1 += "mnop";
	cout << "9. " << s1 << endl;
	s4 = "qrst-" + s2;
	cout << "10. " << s4 << endl;
	s1 = s2 + s4 + " uvw " + "xyz";
	cout << "11. " << s1 << endl;
	qsort(SArray, 4, sizeof(MyString), CompareString);
	for (int i = 0; i < 4; i++)
		cout << SArray[i] << endl;
	//s1的从下标0开始长度为4的子串
	cout << s1(0, 4) << endl;
	//s1的从下标5开始长度为10的子串
	cout << s1(5, 10) << endl;
	return 0;
}
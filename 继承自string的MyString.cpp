#include <cstdlib>
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
class MyString :public string
{
private:
	string str;
	int len;
public:

	MyString(string s) {
		str = s;
		len = s.length();
	}
	MyString() {
		str = "";
		len = 0;
	}
	MyString(const char* s) {
		this->len = sizeof(*s) / sizeof('a');
		this->str = s;
	}
	string operator()(int start, int length) {
		string res = "";
		for (int i = start; (i < start + length) && (i < len); i++) {
			res.push_back(str[i]);
		}
		return res;
	}
	friend ostream& operator<<(ostream& os, MyString& s) {
		os << s.str;
		return os;
	}

	MyString operator+(MyString ss) {
		string res;
		res.append(this->str);
		res.append(ss.str);
		MyString result(res);
		return result;
	}
	MyString operator+(const char* s) {
		return *this + MyString(s);
	}
	friend MyString operator+(const char* s, MyString ss) {
		return MyString(s) + ss;
	}

	char& operator[](int index) {
		return this->str[index];
	}

	MyString& operator+=(string s) {
		this->str = this->str + s;
		this->len = this->len + s.length();
		return *this;
	}

	friend bool operator<(const MyString a, const MyString b) {
		return a.str < b.str;
	}
};


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
	sort(SArray, SArray + 4);
	for (int i = 0; i < 4; i++)
		cout << SArray[i] << endl;
	//s1的从下标0开始长度为4的子串
	cout << s1(0, 4) << endl;
	//s1的从下标5开始长度为10的子串
	cout << s1(5, 10) << endl;
	return 0;
}
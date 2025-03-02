#include <iostream> 
#include <cstring> 
#include <cstdlib> 
#include <cstdio> 
using namespace std;
const int MAX = 110;
class CHugeInt {
	// 在此处补充你的代码
private:
    int digits[210]; // 低位在前，高位在后存储
    int size;
public:
    CHugeInt(const char* s) {
        size = strlen(s);
        for (int i = 0; i < size; ++i)
            digits[i] = s[size - 1 - i] - '0';
    }
    CHugeInt(int n) {
        size = 0;
        do {
            digits[size++] = n % 10;
            n /= 10;
        } while (n);
    }
    CHugeInt operator+(const CHugeInt& b) const {
        CHugeInt res(0);
        res.size = 0;
        int carry = 0, i;
        for (i = 0; i < size || i < b.size || carry; ++i) {
            int sum = carry;
            if (i < size) sum += digits[i];
            if (i < b.size) sum += b.digits[i];
            res.digits[res.size++] = sum % 10;
            carry = sum / 10;
        }
        return res;
    }
    CHugeInt operator+(int n) const {
        return *this + CHugeInt(n);
    }
    friend CHugeInt operator+(int n, const CHugeInt& b) {
        return CHugeInt(n) + b;
    }
    CHugeInt& operator+=(int n) {
        *this = *this + CHugeInt(n);
        return *this;
    }
    CHugeInt& operator++() {
        *this = *this + 1;
        return *this;
    }
    CHugeInt operator++(int) {
        CHugeInt temp = *this;
        *this = *this + 1;
        return temp;
    }
    friend ostream& operator<<(ostream& out, const CHugeInt& num) {
        for (int i = num.size - 1; i >= 0; --i)
            out << num.digits[i];
        return out;
    }
};
int  main()
{
	char s[210];
	int n;

	while (cin >> s >> n) {
		CHugeInt a(s);
		CHugeInt b(n);

		cout << a + b << endl;
		cout << n + a << endl;
		cout << a + n << endl;
		b += n;
		cout << ++b << endl;
		cout << b++ << endl;
		cout << b << endl;
	}
	return 0;
}
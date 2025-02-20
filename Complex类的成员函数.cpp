#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;
class Complex {
private:
    double r, i;
public:
    void Print() {
        cout << r << "+" << i << "i" << endl;
    }
    // 在此处补充你的代码
    Complex& operator=(const char* str) {
        // 使用 sscanf 解析字符串
        sscanf(str, "%lf+%lfi", &r, &i);
        // 在本地VS上跑要改成 sscanf_s
        return *this;
    }
};
int main() {
    Complex a;
    a = "3+4i"; a.Print();
    a = "5+6i"; a.Print();
    return 0;
}
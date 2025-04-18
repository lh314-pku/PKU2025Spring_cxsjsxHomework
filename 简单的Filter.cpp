#include <iostream>
#include <string>
using namespace std;
// 在此处补充你的代码
template<typename T, typename Func>
T* Filter(T* begin, T* end, T* result, Func func) {
    T* current = result;  // 用于记录结果数组当前位置
    for (T* iter = begin; iter != end; ++iter) {
        if (func(*iter)) {  // 如果当前元素满足条件
            *current = *iter;  // 将元素拷贝到结果数组
            ++current;  // 移动结果数组指针
        }
    }
    return current;  // 返回结果数组的最后一个位置的后继
}

bool LargerThan2(int n)
{
	return n > 2;
}
bool LongerThan3(string s) 
{
	return s.length() > 3;
}

string as1[5] = {"Tom","Mike","Jack","Ted","Lucy"};
string as2[5];
int  a1[5] = { 1,2,3,4,5};
int a2[5];
int main() {
	string * p = Filter(as1,as1+5,as2,LongerThan3);
	for(int i = 0;i < p - as2; ++i)
		cout << as2[i];
	cout << endl; 
	int * p2 = Filter(a1,a1+5,a2,LargerThan2);
	for(int i = 0;i < p2-a2; ++i)
		cout << a2[i] << ",";
	return 0;
}
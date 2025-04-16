#include <iostream>
#include <string>
using namespace std;
template <class T>
T SumArray(
// 在此处补充你的代码
T* begin, T* end){
    T sum = T();          // 初始化 sum，使用 T 类型的默认构造函数
    while (begin != end) {// 遍历数组
        sum += *begin;    // 将每个数组中的值累加到 sum 中
        ++begin;          // 移动到下一个元素
    }
    return sum;           // 返回最终的和
}
int main() {
	string array[4] = { "Tom","Jack","Mary","John"};
	cout << SumArray(array,array+4) << endl;
	int a[4] = { 1, 2, 3, 4};  //提示：1+2+3+4 = 10
	cout << SumArray(a,a+4) << endl;
	return 0;
}
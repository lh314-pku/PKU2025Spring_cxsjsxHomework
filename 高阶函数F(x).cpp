#include <iostream>
using namespace std;
// 在此处补充你的代码
template<typename T1, typename T2>
auto f(T1 n) {
    return [n](T2 x) -> decltype(x + n) {  // 使用 Lambda 表达式，返回一个函数
        // decltype自动推导返回类型
        return x + n;                     // 函数功能是计算 x + n
    };
}

int main()
{
   cout << f<int,int>(7)(9) << endl;   //16
   cout << f<string,string> (" hello!")("world")  <<endl; // world hello!
   cout << f<char,string> ('!')("world") << endl;
   
   
   return 0;    //world!
}
#include <iostream>
using namespace std;
// 在此处补充你的代码
template<typename Func1, typename Func2, typename ArgType>
auto combine(Func1 f, Func2 g) {
    return [f, g](ArgType x) -> decltype(f(f(x) + g(x))) { // Lambda 返回一个函数
        return f(f(x) + g(x)); // 使用 f(f(x) + g(x)) 模式
    };
}
int main()
{
    auto Square = [] (double a) { return a * a; };
    auto Inc = [] (double a) { return a + 1; };
    cout << combine<decltype(Square),decltype(Inc),int>(Square,Inc)(3) << endl;
    cout << combine<decltype(Inc),decltype(Square),double>(Inc,Square)(2.5) << endl;

    return 0;
}
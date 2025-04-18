#include <iostream>
#include <string>

using namespace std;
template <class T>
class CMyistream_iterator
{
// 在此处补充你的代码
private:
    istream& iss;   // 输入流
    T value;        // 存储值
public:
    CMyistream_iterator(istream& input):iss(input){
        input >> value;
    }// 构造函数
    // 在 main 函数中的 <int>/<string> 指示了 T 的具体类型
    T operator*(){
        return value;
    }// 重载*，返回当前存储的值
    CMyistream_iterator& operator++(int){
        iss >> value;
        return *this;
    }// 重载++
};



int main()  
{ 
	int t;
	cin >> t;
	while( t -- ) {
		 CMyistream_iterator<int> inputInt(cin);
		 int n1,n2,n3;
		 n1 = * inputInt; //读入 n1
		 int tmp = * inputInt;
		 cout << tmp << endl;
		 inputInt ++;   
		 n2 = * inputInt; //读入 n2
		 inputInt ++;
		 n3 = * inputInt; //读入 n3
		 cout << n1 << " " << n2<< " " << n3 << " ";
		 CMyistream_iterator<string> inputStr(cin);
		 string s1,s2;
		 s1 = * inputStr;
		 inputStr ++;
		 s2 = * inputStr;
		 cout << s1 << " " << s2 << endl;
	}
	 return 0;  
}
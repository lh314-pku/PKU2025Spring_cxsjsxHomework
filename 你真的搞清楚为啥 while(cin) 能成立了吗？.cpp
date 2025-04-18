#include <iostream>
using namespace std;
class MyCin
{
// 在此处补充你的代码
private:
    bool value;
public:
    MyCin(){value = true;}
    MyCin& operator>>(int& n){
        if(value){
            cin >> n;
            if(n == -1){
                value = false;
            }
        }
        return *this;
    }// 重载>>
    operator bool() const{
        return value;
    }// 类型转换为 bool 值
};
int main()
{
    MyCin m;
    int n1,n2;
    while( m >> n1 >> n2) 
        cout  << n1 << " " << n2 << endl;
    return 0;
}
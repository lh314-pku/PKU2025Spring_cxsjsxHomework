#include <iostream>
#include <map>
#include <set>
using namespace std;
int main(){
    int n = 0;
    cin >> n;
    set<int> s;     // 存储整数
    map<int, int> m;// 存储数字的出现次数
    // 什么SM（
    string input = "";
    int num = 0;
    while(n--){
        cin >> input >> num;
        cin.ignore();
        if(input == "add"){
            if(s.count(num) == 0){
                s.insert(num);
                m[num] = 1;
            }
            else{
                m[num]++;
            }
            cout << m[num] << endl;
        }
        else if(input == "ask"){
            if(s.count(num) == 0){
                cout << 0 << ' ' << 0 << endl;
            }
            else{
                cout << 1 << ' ' << m[num] << endl;
            }
        }
        else if(input == "del"){
            cout << m[num] << endl;
            m[num] = 0;
        }
        else{
            cout << "InputError" << endl;
        }
    }
    return 0;
}
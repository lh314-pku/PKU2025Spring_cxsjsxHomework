#include <iostream>
#include <string>
#include <map>
#include <iterator>
#include <algorithm>
using namespace std;
// 在此处补充你的代码
template<class Key, class Value, class Compare=less<Key>>
class MyMultimap {
public:
    using iterator = typename multimap<Key, Value, Compare>::iterator;
    
    // 内部存储使用标准库 multimap
    multimap<Key, Value, Compare> mmap;

    // 插入键值对
    void insert(pair<Key, Value> p) {
        mmap.insert(p);
    }
    
    // 返回迭代器开始位置
    iterator begin() {
        return mmap.begin();
    }
    
    // 返回迭代器结束位置
    iterator end() {
        return mmap.end();
    }
    
    // 查找指定的键
    iterator find(const Key &key) {
        return mmap.find(key);
    }

    // 修改符合条件的键的值为 value
    void Set(const Key &key, const Value &value) {
        auto range = mmap.equal_range(key); // 找到所有键为 key 的范围
        for (auto it = range.first; it != range.second; ++it) {
            it->second = value;
        }
    }

    // 清空 multimap
    void clear() {
        mmap.clear();
    }
};
struct Student 
{
	string name;
	int score;
};
template <class T>
void Print(T first,T last) {
	for(;first!= last; ++ first)
		cout << * first << ",";
	cout << endl;
}
// 定义一个模板 MyMultimap，用于实现类似于 multimap 的操作

int main()
{
	
	Student s[] = { {"Tom",80},{"Jack",70},
					{"Jone",90},{"Tom",70},{"Alice",100} };
	
	MyMultimap<string,int> mp;
	for(int i = 0; i<5; ++ i)
		mp.insert(make_pair(s[i].name,s[i].score));
	Print(mp.begin(),mp.end()); //按姓名从大到小输出

	mp.Set("Tom",78); //把所有名为"Tom"的学生的成绩都设置为78
	Print(mp.begin(),mp.end());
	
	
	
	MyMultimap<int,string,less<int> > mp2;
	for(int i = 0; i<5; ++ i) 
		mp2.insert(make_pair(s[i].score,s[i].name));
	
	Print(mp2.begin(),mp2.end()); //按成绩从小到大输出
	mp2.Set(70,"Error");          //把所有成绩为70的学生，名字都改为"Error"
	Print(mp2.begin(),mp2.end());
	cout << "******" << endl;
	
	mp.clear();
	
	string name;
	string cmd;
	int score;		
	while(cin >> cmd ) {
		if( cmd == "A") {
			cin >> name >> score;
			if(mp.find(name) != mp.end() ) {
				cout << "erroe" << endl;
			}
			mp.insert(make_pair(name,score));
		}
		else if(cmd == "Q") {
			cin >> name;
			MyMultimap<string,int>::iterator p = mp.find(name);
			if( p!= mp.end()) {
				cout << p->second << endl;
			}
			else {
				cout << "Not Found" << endl; 
			}		
		}
	}
	return 0;
}
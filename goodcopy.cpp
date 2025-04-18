#include <iostream>
using namespace std;

template <class T>
struct GoodCopy {
// 在此处补充你的代码
public:
    // 重载()，使得GoodCopy的对象可以像函数一样调用。
    // 而且是循环复制
    void operator()(T* start, T* end, T* goal){
        T* copy_start = goal + (end - start);
        do{
            *copy_start = *end;
            --end;
            --copy_start;
        }while(start != end+1);
    }
    // 如果正向循环，会发现自我复制时会发生覆盖行为
    // 所以采用反向复制
};

int a[200];
int b[200];
string c[200];
string d[200];

template <class T>
void Print(T s,T e) {
	for(; s != e; ++s)
		cout << * s << ",";
	cout << endl;
}

int main()
{
	int t;
	cin >> t;
	while( t -- ) {
		int m ;
		cin >> m;
		for(int i = 0;i < m; ++i)
			cin >> a[i];
		GoodCopy<int>()(a,a+m,b);
		Print(b,b+m);
		GoodCopy<int>()(a,a+m,a+m/2);
		Print(a+m/2,a+m/2 + m);

		for(int i = 0;i < m; ++i)
			cin >> c[i];
		GoodCopy<string>()(c,c+m,d);
		Print(c,c+m);
		GoodCopy<string>()(c,c+m,c+m/2);
		Print(c+m/2,c+m/2 + m);
	}
	return 0;
}
#include <iostream>
#include <cstring>
using namespace std;
template <int bitNum>
struct MyBitset
{
	char a[bitNum / 8 + 1];
	MyBitset() { memset(a, 0, sizeof(a)); };
	void Set(int i, int v) {
		char& c = a[i / 8];
		int bp = i % 8;
		if (v)
			c |= (1 << bp);
		else
			c &= ~(1 << bp);
	}
	// 在此处补充你的代码
	// 内部类 BitReference，用于支持引用语义
	class BitReference {
	private:
		MyBitset& parent; // 引用外部类 MyBitset
		int index;         // 引用的位索引
	public:
		BitReference(MyBitset& parent, int index) : parent(parent), index(index) {}

		// 支持赋值：将值 `v` 赋给特定位
		BitReference& operator=(int v) {
			parent.Set(index, v); // 调用 MyBitset 的 Set 方法
			return *this;
		}

		// 支持赋值链：将另一位的值赋给自己
		BitReference& operator=(const BitReference& other) {
			int value = parent[other.index];
			parent.Set(index, value); // 同样利用 Set 方法
			return *this;
		}

		// 隐式类型转换：返回特定位的值
		operator int() const {
			const char& c = parent.a[index / 8];
			int bp = index % 8;
			return (c >> bp) & 1; // 提取目标位的值
		}
	};

	// 提供访问位值的方法
	int operator[](int i) const {
		const char& c = a[i / 8];
		int bp = i % 8;
		return (c >> bp) & 1; // 提取特定位值
	}

	// 返回位引用，用于修改特定位
	BitReference operator[](int i) {
		return BitReference(*this, i);
	}

	void Print() {
		for (int i = 0; i < bitNum; ++i)
			cout << (*this)[i];
		cout << endl;
	}

};

int main()
{
	int n;
	int i, j, k, v;
	while (cin >> n) {
		MyBitset<20> bs;
		for (int i = 0; i < n; ++i) {
			int t;
			cin >> t;
			bs.Set(t, 1);
		}
		bs.Print();
		cin >> i >> j >> k >> v;
		bs[k] = v;
		bs[i] = bs[j] = bs[k];
		bs.Print();
		cin >> i >> j >> k >> v;
		bs[k] = v;
		(bs[i] = bs[j]) = bs[k];
		bs.Print();
	}
	return 0;
}
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int LivePoint = 0;  // 各司令部起始生命元个数
string tick = "000";// 进行时间

struct People {
	string name;
	int HP;

	People(string n, int hp) :name(n), HP(hp) {}
}; // 武士结构体，包含 其种类和初始生命值 及其 构造函数

class HeadQuarters {
private:
	string side;           // 司令部所属
	int LP;                // 各司令部剩余生命元个数
	vector<int> nums;      // 各武士数量
	int turn;              // 武士编号
	vector<People> peoples;// 制造武士顺序 及 数据
	vector<bool> makeable; // 该武士是否可被制作
	bool stop;             // 司令部是否停止制作
	bool output;           // 后续是否继续输出
	int position;          // 当前制作进度
public:
	HeadQuarters(string s, int n, vector<People> shunxu) {
		this->side = s;
		this->LP = n;
		this->peoples = shunxu;
		for (int i = 0; i < 5; i++) {
			nums.push_back(0);
			makeable.push_back(true);
		}
		turn = 0;
		stop = false;
		output = true;
		position = 0;
	}// 构造函数

	~HeadQuarters() {

	}

	void birth() {
		int i = 0;
		do {
			makeable[position] = (peoples[position].HP <= LP);
			if (makeable[position]) {
				LP -= peoples[position].HP;
				nums[position]++;
				turn++;
				break;
			}
			else {
				i++;
				if (position >= 4) {
					position = 0;
				}
				else {
					position++;
				}
			}

			if (i >= 5) {
				stop = true;
				break;
			}
		} while (!stop);
	}// 每诞生一个武士的处理 / 无法在产生武士处理

	void printout() {
		if (stop && output) {
			cout << tick << ' ' << side << " headquarter stops making warriors" << endl;
			output = false;
		}
		else if (!stop) {
			cout << tick << ' ' << side << ' ' << peoples[position].name << ' ' << turn << " born with strength " << peoples[position].HP << ',' << nums[position] << ' ' << peoples[position].name << " in " << side << " headquarter" << endl;
			// 注：一定要用 cout 或者 printf 一次性输出
			// 否则会 WA 的（你猜我怎么知道）
			if (position >= 4) {
				position = 0;
			}
			else {
				position++;
			}
		}
	}// 输出结果

	bool end() {
		return stop;
	}// 返回是否结束过程
};

bool is_end(HeadQuarters a, HeadQuarters b) {
	return (a.end() && b.end());
}// 判断该 case 是否结束

void new_time(string& tick) {
	char ch = tick[2] + 1;
	if (ch > '9') {
		ch = ch - 10;
		tick[2] = ch;
		char mm = tick[1] + 1;
		if (mm > '9') {
			mm = mm - 10;
			tick[0] += 1;
		}
		tick[1] = mm;
	}
	else {
		tick[2] = ch;
	}
}// 刷新时间

int main() {
	int n = 0;
	cin >> n;
	for (int i = 1; i <= n; i++) {
		tick = "000";
		cin >> LivePoint;
		cin.ignore();
		int a = 0, b = 0, c = 0, d = 0, e = 0;
		cin >> a >> b >> c >> d >> e;
		cin.ignore();
		cout << "Case:" << i << endl;
		People dragon("dragon", a), ninja("ninja", b), iceman("iceman", c), lion("lion", d), wolf("wolf", e);
		vector<People> ps_red = { iceman, lion, wolf, ninja, dragon };
		vector<People> ps_blue = { lion, dragon, ninja, iceman, wolf };
		HeadQuarters red("red", LivePoint, ps_red);
		HeadQuarters blue("blue", LivePoint, ps_blue);
		do {
			red.birth();
			red.printout();
			blue.birth();
			blue.printout();
			new_time(tick);
		} while (!is_end(red, blue));
	}
	return 0;
}
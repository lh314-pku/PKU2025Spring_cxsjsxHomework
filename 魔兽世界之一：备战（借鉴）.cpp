#include <iostream>
using namespace std;

const int WARRIOR_NUM = 5;	// 武士的种类数量

// 武士类
class Warriors
{
public:
	Warriors(int strength, int kindNo);
	static int WarriorsLife[WARRIOR_NUM];	// 武士生命值,按编号


private:
	int no;					// 当前武士的编号
	int kindNo;				// 种类编号
};

int Warriors::WarriorsLife[WARRIOR_NUM] = { 0 };

Warriors::Warriors(int no, int kindNo)
{
	this->no = no;
	this->kindNo = kindNo;
}

// 司令部类
class Headquarter
{
public:
	Headquarter(int color, int lifeValue);		// 根据颜色和生命值创建司令部
	~Headquarter();
	void Making(int time);			// 根据时间生产武士
	bool getStopState();			// 返回是否停止生产
	string getColorByNo(int color);	// 通过数值获取当前司令部颜色

private:
	int lifeValue;			// 司令部生命元
	static int bornSequence[2][WARRIOR_NUM];	// 武士生产顺序
	int color;				// 司令部颜色
	int totalWarriors;		// 生产的武士总数
	int warriorNum[WARRIOR_NUM];	// 当前种类的武士数量
	Warriors* pWarriors[100];	// 假设最多生产100个武士
	bool isStopped;			// 是否停止生产
	int sequence;			// 生产编号
	static string warriorName[WARRIOR_NUM];	// 武士名称
};

// 0 dragon 、1 ninja、2 iceman、3 lion、4 wolf 
int Headquarter::bornSequence[2][WARRIOR_NUM] = { {2,3,4,1,0},{3,0,1,2,4} };
string Headquarter::warriorName[WARRIOR_NUM] = { "dragon","ninja","iceman","lion","wolf" };

Headquarter::Headquarter(int color, int lifeValue)
{
	this->lifeValue = lifeValue;
	this->color = color;
	totalWarriors = 0;
	for (int i = 0; i < WARRIOR_NUM; i++)
	{
		warriorNum[i] = 0;
	}
	isStopped = false;
	sequence = 0;
}

Headquarter::~Headquarter()
{
	for (int i = 0; i < totalWarriors; i++)
	{
		delete pWarriors[i];
	}
}

string Headquarter::getColorByNo(int color)
{
	if (color == 0)
	{
		return "red";
	}
	else
	{
		return "blue";
	}
}

void Headquarter::Making(int time)
{
	// 首先判断是否停止
	if (isStopped)
	{
		return;
	}

	int times = 0;		// 寻找可生产武士的次数
	// 如果搜索次数大于武士数量，则退出
	while (Warriors::WarriorsLife[bornSequence[color][sequence]] > lifeValue &&
		times < WARRIOR_NUM)
	{
		sequence = (sequence + 1) % WARRIOR_NUM;
		times++;
	}

	// 当前要生产的武士编号
	int kindNo = bornSequence[color][sequence];
	// 如果生命元不足以生产武士
	if (Warriors::WarriorsLife[kindNo] > lifeValue)
	{
		isStopped = true;
		if (color == 0)
			printf("%03d red headquarter stops making warriors\n", time);
		else
			printf("%03d blue headquarter stops making warriors\n", time);
		return;
	}
	// 如果能生产
	lifeValue -= Warriors::WarriorsLife[kindNo];
	sequence = (sequence + 1) % WARRIOR_NUM;
	pWarriors[totalWarriors] = new Warriors(totalWarriors + 1, kindNo);
	warriorNum[kindNo]++;
	// 输出
	printf("%03d %s %s %d born with strength %d,%d %s in %s headquarter\n",
		time, getColorByNo(color).c_str(), warriorName[kindNo].c_str(),
		++totalWarriors, Warriors::WarriorsLife[kindNo], warriorNum[kindNo],
		warriorName[kindNo].c_str(), getColorByNo(color).c_str());
	return;
}

bool Headquarter::getStopState()
{
	return isStopped;
}



int main()
{
	int dataNum;		// 数据总数
	cin >> dataNum;
	int cases = 1;		// 编号
	while (dataNum--)
	{
		// 创建两个司令部
		int lifeValue = 0;
		cin >> lifeValue;
		// 初始化武士生命值
		for (int i = 0; i < WARRIOR_NUM; i++)
		{
			cin >> Warriors::WarriorsLife[i];
		}
		Headquarter red(0, lifeValue), blue(1, lifeValue);
		// 生产武士
		cout << "Case:" << cases++ << endl;
		int times = 0;
		while (1)
		{
			red.Making(times);
			blue.Making(times);
			if (red.getStopState() && blue.getStopState())
			{
				// 如果两个司令部都停止生产则退出
				break;
			}
			times++;		// 时间累加
		}
	}

	return 0;
}
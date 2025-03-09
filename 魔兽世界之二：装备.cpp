#include<iostream>
using namespace std;

#define WarriorNum 5
#define WarriorsMax 10000 //武士数量上限
#define WeaponNum 3


int WarriorLife[WarriorNum] = {};
char colors[2][5] = { "red", "blue" };
char WarriorsName[WarriorNum][10] = { "dragon" ,"ninja","iceman","lion","wolf" };
char WeaponName[WeaponNum][10] = { "sword", "bomb","arrow" };

class Headquarters;
class Warrior;
class Dragon;
class Ninja;
class Iceman;
class Lion;
class Wolf;
class Weapon;
class sword;
class bomb;
class arrow;

class Weapon {
private:
    int attack;
    int defend;
    int Type;
public:
    void Init(int _Type) {
        Type = _Type;
    }
    int GetWeapon() { return Type; }
};


class Warrior {
protected:
    int Life;
    int Type; //武士类别,分别是dragon 、ninja、iceman、lion、wolf
    int ArrayNum; //武士队列编号
    Headquarters* team; //指针指回Head，省下很多参数
public:
    Warrior(Headquarters* p, int _ArrayNum) :team(p), ArrayNum(_ArrayNum) {}
    virtual void PrintProduce(int time) = 0;
    void PrintProduce(int time, int);
    virtual ~Warrior() {};
};


class Headquarters {
private:
    int Life;
    int Color; //0是红，1是蓝。
    Warrior* WarriorsArray[WarriorsMax]; //武士队列
    int WarriorsArrayNum;
    int Warrior_MakeSeq[WarriorNum];//该司令部生产序列
    int MakeNum; //当前生产序列编号
    bool ProduceState;
    int WarriorsNums[WarriorNum]; //对应武士数量
public:
    Headquarters(int _Color, int _Life, int* _Warrior_MakeSeq) :Color(_Color), Life(_Life) {
        for (int i = 0; i < WarriorNum; i++) {
            Warrior_MakeSeq[i] = _Warrior_MakeSeq[i];
            WarriorsNums[i] = 0;
        }
        WarriorsArrayNum = 0;
        MakeNum = 0;
        ProduceState = true;
    }
    ~Headquarters() {
        for (int i = 0; i < WarriorsArrayNum; i++) delete WarriorsArray[i];
    }

    bool produce(int time);
    int GetLife() { return Life; }
    int GetColor() { return Color; }
    int GetWarriorsNums(int Type) { return WarriorsNums[Type]; }
};

void Warrior::PrintProduce(int time, int) {
    int color = team->GetColor();
    printf("%03d %s %s %d born with strength %d,%d %s in %s headquarter\n",
        time, colors[color], WarriorsName[Type], ArrayNum,
        Life, team->GetWarriorsNums(Type), WarriorsName[Type], colors[color]);
};

// Dragon，Ninja，Lions，Wolf，Iceman都继承自Warrior
class Dragon :public Warrior {
private:
    Weapon wp;
    float Morale;
public:
    Dragon(Headquarters* p, int _ArrayNum) :Warrior(p, _ArrayNum) {
        Type = 0;
        Life = WarriorLife[Type];
        wp.Init(ArrayNum % WeaponNum);
        Morale = team->GetLife() * 1.0 / Life;
    }
    virtual void PrintProduce(int time) {
        Warrior::PrintProduce(time, 0);
        printf("It has a %s,and it's morale is %.02f\n", WeaponName[wp.GetWeapon()], Morale);
    }
    //    virtual ~Dragon();
};

class Ninja :public Warrior {
private:
    Weapon wp[2];
public:
    Ninja(Headquarters* p, int _ArrayNum) :Warrior(p, _ArrayNum) {
        Type = 1;
        Life = WarriorLife[Type];
        wp[0].Init(ArrayNum % WeaponNum);
        wp[1].Init((ArrayNum + 1) % WeaponNum);
    }
    virtual void PrintProduce(int time) {
        Warrior::PrintProduce(time, 0);
        printf("It has a %s and a %s\n", WeaponName[wp[0].GetWeapon()], WeaponName[wp[1].GetWeapon()]);
    }
    // virtual ~Ninja();
};

class Iceman :public Warrior {
private:
    Weapon wp;
public:
    Iceman(Headquarters* p, int _ArrayNum) :Warrior(p, _ArrayNum) {
        Type = 2;
        Life = WarriorLife[Type];
        wp.Init(ArrayNum % WeaponNum);
    }
    virtual void PrintProduce(int time) {
        Warrior::PrintProduce(time, 0);
        printf("It has a %s\n", WeaponName[wp.GetWeapon()]);
    }
    //virtual ~Iceman();
};

class Lion :public Warrior {
private:
    int loyalty;
public:
    Lion(Headquarters* p, int _ArrayNum) :Warrior(p, _ArrayNum) {
        Type = 3;
        Life = WarriorLife[Type];
        loyalty = team->GetLife();
    }
    virtual void PrintProduce(int time) {
        Warrior::PrintProduce(time, 0);
        printf("It's loyalty is %d\n", loyalty);
    }
    //virtual ~Lion();
};

class Wolf :public Warrior {
public:
    Wolf(Headquarters* p, int _ArrayNum) :Warrior(p, _ArrayNum) {
        Type = 4;
        Life = WarriorLife[Type];
    }
    virtual void PrintProduce(int time) {
        Warrior::PrintProduce(time, 0);
    }
    //    virtual ~Wolf();
};

bool Headquarters::produce(int time) {
    if (ProduceState == false) return false;
    for (int i = 0; i < WarriorNum; i++) {
        if (Life >= WarriorLife[Warrior_MakeSeq[(MakeNum + i) % WarriorNum]]) {
            MakeNum = (MakeNum + i) % WarriorNum;
            ProduceState = true;
            Life -= WarriorLife[Warrior_MakeSeq[MakeNum]];
            switch (Warrior_MakeSeq[MakeNum]) { //{"dragon" ,"ninja","iceman","lion","wolf"};
            case 0:
                WarriorsArray[WarriorsArrayNum] = new Dragon(this, WarriorsArrayNum + 1);
                break;
            case 1:
                WarriorsArray[WarriorsArrayNum] = new Ninja(this, WarriorsArrayNum + 1);
                break;
            case 2:
                WarriorsArray[WarriorsArrayNum] = new Iceman(this, WarriorsArrayNum + 1);
                break;
            case 3:
                WarriorsArray[WarriorsArrayNum] = new Lion(this, WarriorsArrayNum + 1);
                break;
            case 4:
                WarriorsArray[WarriorsArrayNum] = new Wolf(this, WarriorsArrayNum + 1);
                break;
            }
            WarriorsNums[Warrior_MakeSeq[MakeNum]]++;
            WarriorsArray[WarriorsArrayNum++]->PrintProduce(time);
            MakeNum = (MakeNum + 1) % WarriorNum;
            return true;
        }
    }
    //上面没有return true则说明已经无法制造士兵了
    ProduceState = false;
    printf("%03d %s headquarter stops making warriors\n", time, colors[Color]);
    return false;

}


int main() {
    int n, m;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cout << "Case:" << i << endl;
        cin >> m;
        for (int i = 0; i < WarriorNum; i++) {
            cin >> WarriorLife[i];
        }
        int Head_Red_Warrior_MakeSeq[WarriorNum] = { 2,3,4,1,0 };
        int Head_Blue_Warrior_MakeSeq[WarriorNum] = { 3,0,1,2,4 };
        Headquarters Head_Red(0, m, Head_Red_Warrior_MakeSeq);
        Headquarters Head_Blue(1, m, Head_Blue_Warrior_MakeSeq);
        bool Red_flag = true, Blue_flag = true; //
        int time = 0;
        while (Red_flag == true || Blue_flag == true) {
            Red_flag = Head_Red.produce(time);
            Blue_flag = Head_Blue.produce(time);
            time++;
        }
    }
    return 0;
}
#include <iostream>
#include <cstring>
#include <algorithm>
#include <iomanip>
using namespace std;
// 武器类（基类）
class Weapon{
public:
    int weaponId; // 武器编号
    int ad;       // 武器攻击力
    int available;// 武器使用次数
    string typeName;// 武器名称

    Weapon(int weaponId_, int ad_, int available_, string name) : weaponId(weaponId_), ad(ad_), available(available_), typeName(name){}
};
// 三种武器继承自 Weapon 类
class Sword: public Weapon{
public:
    Sword(int weaponId_, int ad_): Weapon(weaponId_, ad_, 999, "sword") {}
};
class Bomb: public Weapon{
public:
    Bomb(int weaponId_, int ad_): Weapon(weaponId_, ad_, 1, "bomb") {}
};
class Arrow: public Weapon{
public:
    Arrow(int weaponId_, int ad_): Weapon(weaponId_, ad_, 3, "arrow") {}
};

// 武士类（基类）
class Soldier{
public:
    int headId;        // 所属阵营
    int soldierId;     // 编号
    int hp, ad;        // 生命值，攻击力
    int weaponNumber;  // 所持武器数量
    int type, location;// 武士类型，位置
    // 0:dragon 1:ninja 2:iceman 3:lion 4:wolf
    // int loyalty;       // 忠诚度
    // float morale;      // 士气

    string typeName;   // 武士名称
    int weaponClass[3];// 各种武器数量
    Weapon* weaponList[10];// 所持武器（复数）
    Soldier(int headId_, int soldierId_, int hp_, int ad_, int location_, int type_, string typeName_): headId(headId_), soldierId(soldierId_), hp(hp_), ad(ad_), location(location_), type(type_), typeName(typeName_){
        for(int i = 0; i < 10; ++i)
			weaponList[i] = nullptr; 
		memset(weaponClass, 0, sizeof(weaponClass));
    }
    ~Soldier(){
        for(int i = 0; i < 10; i++){
            delete weaponList[i];
        }
    }

    void ChooseWeapon(int n){
        switch(n){
        case 0:weaponList[weaponNumber++] = new Sword(0, ad * 2 / 10);
                ++weaponClass[n];
                break;
        case 1:weaponList[weaponNumber++] = new Bomb(1, ad * 4 / 10);
                ++weaponClass[n];
                break;
        case 2:weaponList[weaponNumber++] = new Arrow(2, ad * 3 / 10);
                ++weaponClass[n];
                break;
        default:cout << "weapon choose error" << endl;
        }
    }
};
// 五种武士继承自 Soldier 类
class Dragon : public Soldier{
public:
    float morale;// 士气
    Dragon(int headId_, int soldier_, int hp_, int ad_, int location_, float morale_) : Soldier(headId_, soldierId, hp_, ad_, location_, 0, "dragon"){
        morale = morale_;
        ChooseWeapon(soldierId % 3);
    }
};
class Ninja : public Soldier{
public:
    Ninja(int headId_, int soldierId_, int hp_, int ad_, int location_): Soldier(headId_, soldierId_, hp_, ad_, location_, 1, "ninja") { 
        ChooseWeapon(soldierId % 3);
        ChooseWeapon((soldierId+1) % 3);
    }
};
class Iceman : public Soldier{
public:
    Iceman(int headId_, int soldierId_, int hp_, int ad_, int location_): Soldier(headId_, soldierId_, hp_, ad_, location_, 2, "iceman") { 
        ChooseWeapon(soldierId % 3);
    }
};
class Lion : public Soldier{
public:
    int loyalty;// 忠诚度
    Lion(int headId_, int soldierId_, int hp_, int ad_, int loyalty_, int location_): Soldier(headId_, soldierId_, hp_, ad_, location_, 3, "lion") { 
		ChooseWeapon(soldierId % 3);
        loyalty = loyalty_;
	}
};
class Wolf : public Soldier{
public:
    Wolf(int headId_, int soldierId_, int hp_, int ad_, int location_): Soldier(headId_, soldierId_, hp_, ad_, location_, 4, "wolf") { }
};

// 司令部类
class Headquarter{
public:
    int hp;    // 剩余生命元
    int number;// 阵营士兵数量
    int headId;// 阵营
    // 武士制造顺序
    int* order;
    int* p = order;

    int whereSoldier[24];
    Soldier* soldierList[110];
    Headquarter(int hp_, int headId_, int* order_) : hp(hp_), headId(headId_), order(order_){
        number = 0;
        for(int i = 0; i < 110; i++){
            soldierList[i] = nullptr;
        }
        memset(whereSoldier, 0, sizeof(whereSoldier));
    }
};
// 单独管理游戏对战系统
class CombatSystem{
public:
    int times;

    void start(){
        int t = 0;
        cin >> t;
        cin.ignore();
        for(int t0 = 1; t0 <= t; t0++){
            int M, N, R, K, T;// 司令部生命，城市数，arrow攻击力，忠诚度下降系数，截止时间
            cin >> M >> N >> R >> K >> T;
            cin.ignore();
            int hpSoldier[5];
            for(int i = 0; i < 5; cin >> hpSoldier[i++]);
            int adSoldier[5];
            for(int i = 0; i < 5; cin >> adSoldier[i++]);
            cout << "Case" << t0 << ":" << endl;
            int orderRed[5] = {2, 3, 4, 1, 0}, orderBlue[5] = {3, 0, 1, 2, 4};
            Headquarter red(M, 0, orderRed);
            Headquarter blue(M, 1, orderBlue);
            cout << "start over" << endl;
        }
    }
};

int main(){
    CombatSystem c;
    c.start();
    return 0;
}
#include <iostream>
#include <cstring>
#include <iomanip>
#include <algorithm>
using namespace std;

class Weapon{ 
public:
    int weaponId, ad, available; 
	string typeName;
    
    Weapon(int weaponId_, int ad_, int available_, string typeName_): weaponId(weaponId_), ad(ad_), available(available_), typeName(typeName_) {}
};

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
	Arrow(int weaponId_, int ad_): Weapon(weaponId_, ad_, 2, "arrow") {}
};

class Soldier{ 
public:
	//所属阵营，武士编号，生命，攻击，武器数量，武士类型，武士位置，忠诚度
    int headId, soldierId, hp, ad, weaponNumber, type, location, loyalty;
	//各类别的武器数量
    int weaponClass[3]; 
    string typeName;
	Weapon* weaponList[10]; 

    Soldier(int headId_, int soldierId_, int hp_, int ad_, int location_, int type_, string typeName_, int loyalty_ = 999): headId(headId_), soldierId(soldierId_), hp(hp_), ad(ad_), type(type_), typeName(typeName_), location(location_), loyalty(loyalty_), weaponNumber(0) {
		for(int i = 0; i < 10; ++i)
			weaponList[i] = nullptr; 
		memset(weaponClass, 0, sizeof(weaponClass));
	}
	
	void ChooseWeapon (int n) {
		switch(n) {
			case 0: weaponList[weaponNumber++] = new Sword(0, ad * 2 / 10);
					++weaponClass[0];
					break;
			case 1: weaponList[weaponNumber++] = new Bomb(1, ad * 4 / 10);
					++weaponClass[1];
					break;
			case 2: weaponList[weaponNumber++] = new Arrow(2, ad * 3 / 10);
					++weaponClass[2];
					break;
			default: cout << "!!武器选择错误" << endl; 
		}
		return;
	}
	
	~Soldier() {
		for(int i = 0; i < 10; ++i)
			delete weaponList[i]; 
	}
};

class Dragon: public Soldier{ 
public:
    Dragon(int headId_, int soldierId_, int hp_, int ad_, int location_): Soldier(headId_, soldierId_, hp_, ad_, location_, 0, "dragon") { 
		ChooseWeapon(soldierId % 3);
	}

};

class Ninja: public Soldier{ 
public:
    Ninja(int headId_, int soldierId_, int hp_, int ad_, int location_): Soldier(headId_, soldierId_, hp_, ad_, location_, 1, "ninja") { 
		ChooseWeapon(soldierId % 3);
		ChooseWeapon((soldierId+1) % 3);
	}

};

class Iceman: public Soldier{ 
public:
    Iceman(int headId_, int soldierId_, int hp_, int ad_, int location_): Soldier(headId_, soldierId_, hp_, ad_, location_, 2, "iceman") { 
		ChooseWeapon(soldierId % 3);
	}
};

class Lion: public Soldier{ 
public:
    Lion(int headId_, int soldierId_, int hp_, int ad_, int loyalty_, int location_): Soldier(headId_, soldierId_, hp_, ad_, location_, 3, "lion", loyalty_) { 
		ChooseWeapon(soldierId % 3);
	}
};

class Wolf: public Soldier{ 
public:
    Wolf(int headId_, int soldierId_, int hp_, int ad_, int location_): Soldier(headId_, soldierId_, hp_, ad_, location_, 4, "wolf") { }

};

class Headquarter{ 
public:
    int hp, number, headId;
    int whereSoldier[24];
	//造兵顺序
    int* order;	
    int* p = order;
	
    Soldier* soldierList[110];
    
    Headquarter(int hp_, int headId_, int* order_): hp(hp_), headId(headId_), order(order_), number(0) {
		for(int i = 0; i < 110; ++i)
			soldierList[i] = nullptr; 
		memset(whereSoldier, 0, sizeof(whereSoldier));
	}
    
    void MakeSoldier(int* hpSoldier, int* adSoldier, int cityNumber, int times) {
    	if(hp > hpSoldier[*p]) {
    		switch(*p) {
	    		case 0: hp -= hpSoldier[0];
	    				++number;
						soldierList[number-1] = new Dragon(headId, number, hpSoldier[0], adSoldier[0], headId*(cityNumber+1));
						whereSoldier[headId*(cityNumber+1)] = number;
	    				break;
				case 1: hp -= hpSoldier[1];
						++number;
						soldierList[number-1] = new Ninja(headId, number, hpSoldier[1], adSoldier[1], headId*(cityNumber+1));
						whereSoldier[headId*(cityNumber+1)] = number;
						break;
				case 2: hp -= hpSoldier[2];
						++number;
						soldierList[number-1] = new Iceman(headId, number, hpSoldier[2], adSoldier[2], headId*(cityNumber+1));
						whereSoldier[headId*(cityNumber+1)] = number;
						break;
				case 3: hp -= hpSoldier[3];
						++number;
						soldierList[number-1] = new Lion(headId, number, hpSoldier[3], adSoldier[3], hp, headId*(cityNumber+1));
						whereSoldier[headId*(cityNumber+1)] = number;
						break;
				case 4: hp -= hpSoldier[4];
						++number;
						soldierList[number-1] = new Wolf(headId, number, hpSoldier[4], adSoldier[4], headId*(cityNumber+1));
						whereSoldier[headId*(cityNumber+1)] = number;
						break;
				default: p = order;
						cout << "!!武士选择错误" << endl; 
			}
			if(headId == 0) {
				cout << setw(3) << setfill('0') << times/60 << ':' << setw(2) << setfill('0') << times%60 << " red " << soldierList[number-1]->typeName << ' ' << number << " born" << endl;
				if(*p == 3)
					cout << "Its loyalty is " << soldierList[number-1]->loyalty << endl;
			}
			else if(headId == 1) {
				cout << setw(3) << setfill('0') << times/60 << ':' << setw(2) << setfill('0') << times%60 << " blue " << soldierList[number-1]->typeName << ' ' << number << " born" << endl;
				if(*p == 3)
					cout << "Its loyalty is " << soldierList[number-1]->loyalty << endl;
			}
			
			if(p == order + 4)
				p = order;
			else
				++p;
		}	
		return;
	}
	
	~Headquarter() {
		for(int i = 0; i < 110; ++i)
			delete soldierList[i];
	}
};

//战斗系统 
class CombatSystem {
public:
	int times = 0;
	
	//lion忠诚度判断
	void IfLoyalty(Headquarter& red, Headquarter& blue, int cityNumber) {
		for(int i = 0; i <= cityNumber+1; ++i) {
			int idr = red.whereSoldier[i]-1;
			int idb = blue.whereSoldier[i]-1;
			if(red.whereSoldier[i] != 0 && red.soldierList[idr]->type == 3 && red.soldierList[idr]->loyalty <= 0) {
				red.whereSoldier[i] = 0;
				cout << setw(3) << setfill('0') << times/60 << ':' << setw(2) << setfill('0') << times%60 << " red lion " << idr+1 << " ran away" << endl;
				delete red.soldierList[idr];
				red.soldierList[idr] = nullptr;
			}
			if(blue.whereSoldier[i] != 0 && blue.soldierList[idb]->type == 3 && blue.soldierList[idb]->loyalty <= 0) {
				blue.whereSoldier[i] = 0;
				cout << setw(3) << setfill('0') << times/60 << ':' << setw(2) << setfill('0') << times%60 << " blue lion " << idb+1 << " ran away" << endl;
				delete blue.soldierList[idb];
				blue.soldierList[idb] = nullptr;
			}
		}
	}
	
	//武器排序比较函数
	static int WeaponCmp(Weapon*& w1, Weapon*& w2) {
		if(w1->available == 0)
			return 0;
		else if(w2->available == 0)
			return 1;
		else if(w1->weaponId < w2->weaponId)
			return 1;
		else if(w1->weaponId > w2->weaponId)
			return 0;
		else if(w1->weaponId == 2)
			return w1->available < w2->available;
		else
			return 0;
	}
	
	//武器排序并统计该武士各类武器数量及武器总数
	void CountWeaponNumber(Soldier*& s) {
		sort(s->weaponList, s->weaponList + s->weaponNumber, WeaponCmp);
		int weaponNum = 0;
		int weaponClassNum[3] = {0, 0, 0};
		for(int i = 0; i < s->weaponNumber; ++i) {
			if(s->weaponList[i] != nullptr && s->weaponList[i]->available != 0) {
				weaponNum += 1;
				weaponClassNum[s->weaponList[i]->weaponId] += 1;
			}	
		}
		s->weaponNumber = weaponNum;
		s->weaponClass[0] = weaponClassNum[0];
		s->weaponClass[1] = weaponClassNum[1];
		s->weaponClass[2] = weaponClassNum[2];
		if(s->weaponClass[0] + s->weaponClass[1] + s->weaponClass[2] != s->weaponNumber)
			cout << "!!武器统计错误" << endl; 
		return;
	}
	
	//统计各武士位置
	void CountSoldier(Headquarter& h) {
		memset(h.whereSoldier, 0, sizeof(h.whereSoldier));
		for(int i = 0; i < h.number; ++i) {
			if(h.soldierList[i] != nullptr) {
				CountWeaponNumber(h.soldierList[i]);
				h.whereSoldier[h.soldierList[i]->location] = h.soldierList[i]->soldierId;
			}
		}
		return;
	}
	 
	//武士前进
	int SoldierGo(Headquarter& red, Headquarter& blue, int k, int cityNumber) {
		int headWinFlag = 0;
		for(int i = 0; i <= cityNumber+1; ++i) {
			if(red.whereSoldier[i] != 0) {
				int idr = red.whereSoldier[i]-1;
				red.soldierList[idr]->location++;
				if(red.soldierList[idr]->type == 3 && red.soldierList[idr]->location != (1-red.headId)*(cityNumber+1))
					red.soldierList[idr]->loyalty -= k;
				else if(red.soldierList[idr]->type == 2) 
					red.soldierList[idr]->hp -= red.soldierList[idr]->hp / 10;
			}
			if(blue.whereSoldier[i] != 0) {
				int idb = blue.whereSoldier[i]-1;
				blue.soldierList[idb]->location--;
				if(blue.soldierList[idb]->type == 3 && blue.soldierList[idb] -> location != (1-blue.headId)*(cityNumber+1))
					blue.soldierList[idb]->loyalty -= k;
				else if(blue.soldierList[idb]->type == 2) 
					blue.soldierList[idb]->hp -= blue.soldierList[idb]->hp / 10;
			}
		}
		CountSoldier(red);
		CountSoldier(blue);
		for(int i = 0; i <= cityNumber+1; ++i) {
			if(red.whereSoldier[i] != 0) {
				int idr = red.whereSoldier[i]-1;
				//判断是否到达敌方司令部
				if(red.soldierList[idr]->location >= cityNumber+1) {
					cout << setw(3) << setfill('0') << times/60 << ':' << times%60 << " red " << red.soldierList[idr]->typeName << ' ' << idr+1 << " reached blue headquarter with " << red.soldierList[idr]->hp << " elements and force " << red.soldierList[idr]->ad << endl;
					cout << setw(3) << setfill('0') << times/60 << ':' << times%60 << " blue headquarter was taken" << endl;
					headWinFlag = 1;
				}
				else
					cout << setw(3) << setfill('0') << times/60 << ':' << times%60 << " red " << red.soldierList[idr]->typeName << ' ' << idr+1 << " marched to city " << red.soldierList[idr]->location << " with " << red.soldierList[idr]->hp << " elements and force " << red.soldierList[idr]->ad << endl;
			}
			if(blue.whereSoldier[i] != 0) {
				int idb = blue.whereSoldier[i]-1;
				//判断是否到达敌方司令部
				if(blue.soldierList[idb]->location <= 0) {
					cout << setw(3) << setfill('0') << times/60 << ':' << times%60 << " blue " << blue.soldierList[idb]->typeName << ' ' << idb+1 << " reached red headquarter with " << blue.soldierList[idb]->hp << " elements and force " << blue.soldierList[idb]->ad << endl;
					cout << setw(3) << setfill('0') << times/60 << ':' << times%60 << " red headquarter was taken" << endl;
					headWinFlag = 1;
				}
				else
					cout << setw(3) << setfill('0') << times/60 << ':' << times%60 << " blue " << blue.soldierList[idb]->typeName << ' ' << idb+1 << " marched to city " << blue.soldierList[idb]->location << " with " << blue.soldierList[idb]->hp << " elements and force " << blue.soldierList[idb]->ad << endl;
			}
		}
		return headWinFlag;
	}
	
	//缴获武器
	void GrabWeapon(Soldier*& s1, Soldier*& s2) {
		for(int w1 = s1->weaponNumber, w2 = 0; w1 < 10, w2 < s2->weaponNumber; ++w1, ++w2) {
			if(s2->weaponList[w2]->available > 0) {
				s1->ChooseWeapon(s2->weaponList[w2]->weaponId);
				s1->weaponList[s1->weaponNumber-1]->available = s2->weaponList[w2]->available;
				s2->weaponList[w2]->available = 0;
			}
		}
		CountWeaponNumber(s1);
		CountWeaponNumber(s2);
		return;
	}
	
	//wolf抢武器
	void WolfGrabWeapon(Headquarter& red, Headquarter& blue, int cityNumber) {
		for(int i = 0; i <= cityNumber+1; ++i) {
			int idr = red.whereSoldier[i]-1, idb = blue.whereSoldier[i]-1;
			if(red.whereSoldier[i] != 0 && red.soldierList[idr]->type == 4 && blue.whereSoldier[i] != 0 && blue.soldierList[idb]->type != 4) {
				//被抢方从第一件武器开始找，可用便依次放在wolf的武器列表后面 
				for(int w1 = red.soldierList[idr]->weaponNumber, w2 = 0; w1 < 10, w2 < blue.soldierList[idb]->weaponNumber; ++w1, ++w2) {
					//wolf得到对应武器
					red.soldierList[idr]->ChooseWeapon(blue.soldierList[idb]->weaponList[w2]->weaponId);
					//被抢方的武器可用次数赋值给wolf得到的武器可用次数
					red.soldierList[idr]->weaponList[red.soldierList[idr]->weaponNumber - 1]->available = blue.soldierList[idb]->weaponList[w2]->available;
					//清空被抢方的武器可用次数
					blue.soldierList[idb]->weaponList[w2]->available = 0;
					//wolf只抢一类武器，判断若下一件武器为另一类武器 或没有下一件武器或 wolf自身武器已满10 则结束抢夺，跳出循环并输出抢夺信息
					if(w1 >= 10 || w2 >= blue.soldierList[idb]->weaponNumber || blue.soldierList[idb]->weaponList[w2+1] == nullptr || blue.soldierList[idb]->weaponList[w2+1]->available <= 0 || blue.soldierList[idb]->weaponList[w2]->weaponId != blue.soldierList[idb]->weaponList[w2+1]->weaponId) {
						cout << setw(3) << setfill('0') << times/60 << ':' << times%60 << " red wolf " << idr+1 << " took " << w2+1 << ' ' << blue.soldierList[idb]->weaponList[w2]->typeName << " from blue " << blue.soldierList[idb]->typeName << ' ' << idb+1 << " in city " << i << endl;
						break;
					}
				}
				//抢夺后，重新武器排序并统计数量
				CountWeaponNumber(red.soldierList[idr]);
			}
				
			else if(blue.whereSoldier[i] != 0 && blue.soldierList[idb]->type == 4 && red.whereSoldier[i] != 0 && red.soldierList[idr]->type != 4) {
				for(int w1 = blue.soldierList[idb]->weaponNumber, w2 = 0; w1 < 10, w2 < red.soldierList[idr]->weaponNumber; ++w1, ++w2) {
					blue.soldierList[idb]->ChooseWeapon(red.soldierList[idr]->weaponList[w2]->weaponId);
					blue.soldierList[idb]->weaponList[blue.soldierList[idb]->weaponNumber - 1]->available = red.soldierList[idr]->weaponList[w2]->available;
					red.soldierList[idr]->weaponList[w2]->available = 0;
					if(w1 >= 10 || w2 >= red.soldierList[idr]->weaponNumber || red.soldierList[idr]->weaponList[w2+1] == nullptr || red.soldierList[idr]->weaponList[w2+1]->available <= 0 || red.soldierList[idr]->weaponList[w2]->weaponId != red.soldierList[idr]->weaponList[w2+1]->weaponId) {
						cout << setw(3) << setfill('0') << times/60 << ':' << times%60 << " blue wolf " << idb+1 << " took " << w2+1 << ' ' << red.soldierList[idr]->weaponList[w2]->typeName << " from red " << red.soldierList[idr]->typeName << ' ' << idr+1 << " in city " << i << endl;
						break;
					}
				}
				CountWeaponNumber(blue.soldierList[idb]);
			}
		}
		return;
	}
	
	//检验状态是否改变
	int CheckState(Soldier*& s1, Soldier*& s2) {
		int s1WeaponNum = 0, s2WeaponNum = 0, s1TotalAd = 0, s2TotalAd = 0;
		int s1WeaponClassNum[3] = {0, 0, 0}, s2WeaponClassNum[3] = {0, 0, 0};
		for(int i = 0; i < s1->weaponNumber; ++i) {
			if(s1->weaponList[i] != nullptr && s1->weaponList[i]->available != 0) {
				s1WeaponNum += 1;
				s1WeaponClassNum[s1->weaponList[i]->weaponId] += 1;
				if(s1->weaponList[i]->weaponId == 0)
					s1TotalAd += s1->weaponList[i]->ad;
			}
		}
		for(int j = 0; j < s2->weaponNumber; ++j) {
			if(s2->weaponList[j] != nullptr && s2->weaponList[j]->available != 0) {
				s2WeaponNum += 1;
				s2WeaponClassNum[s2->weaponList[j]->weaponId] += 1;
				if(s2->weaponList[j]->weaponId == 0)
					s2TotalAd += s2->weaponList[j]->ad;
			}
		}
		if((s1WeaponNum == 0 && s2WeaponNum == 0) || (s1TotalAd == 0 && s2TotalAd == 0 && s1WeaponClassNum[1] == 0 && s2WeaponClassNum[1] == 0 && s1WeaponClassNum[2] == 0 && s2WeaponClassNum[2] == 0))
			return 1;
		else
			return 0;
	}

	//战斗
	int Combat(Soldier*& s1, Soldier*& s2) {
		int i1 = 0, i2 = 0, winflag = 0;
		while(winflag == 0) {
			//round一次回合中找武器的次数，找遍了都没有说明他没有可用武器了
			int round1 = 0, round2 = 0;
			//判断该武器是否可用，若不可用，找到可用次数大于0的武器
			while(round1 < s1->weaponNumber && s1->weaponList[i1]->available == 0) {
				++i1;
				if(i1 >= s1->weaponNumber) 
					i1 = 0;
				++round1;
			}
			//s1攻击s2 
			if(round1 < s1->weaponNumber) {
				s2->hp -= s1->weaponList[i1]->ad;
				//炸弹反伤
				if(s1->weaponList[i1]->weaponId == 1 && s1->type != 1) {
					s1->hp -= (s1->weaponList[i1]->ad / 2);
				}	
				if(s1->weaponList[i1]->weaponId != 0) {
					--s1->weaponList[i1]->available;
				}
				//使用后换武器
				++i1;
				if(i1 >= s1->weaponNumber) 
					i1 = 0;
			}
			//战斗结果判断
			if(s2->hp <= 0 && s1->hp <= 0) {
				winflag = 3; //两败俱伤
				break;
			}	
			else if(s2->hp <= 0 && s1->hp > 0) {
				winflag = 1; //第一个人赢
				break;
			}
			else if(s2->hp > 0 && s1->hp <= 0) {
				winflag = 2; //第二个人赢
				break;
			}		
			
			while(round2 < s2->weaponNumber && s2->weaponList[i2]->available == 0) {
				++i2;
				if(i2 >= s2->weaponNumber) 
					i2 = 0;
				++round2;
			}
			//s2攻击s1 
			if(round2 < s2->weaponNumber) {
				s1->hp -= s2->weaponList[i2]->ad;
				if(s2->weaponList[i2]->weaponId == 1 && s2->type != 1) {
					s2->hp -= (s2->weaponList[i2]->ad/2);
				}
				if(s2->weaponList[i2]->weaponId != 0) {
					--s2->weaponList[i2]->available;
				}
				//使用后换武器
				++i2;
				if(i2 >= s2->weaponNumber) 
					i2 = 0;
			}
			
			if(s2->hp <= 0 && s1->hp <= 0) {
				winflag = 3; //两败俱伤
				break;
			}	
			else if(s2->hp <= 0 && s1->hp > 0) {
				winflag = 1; //第一个人赢
				break;
			}
			else if(s2->hp > 0 && s1->hp <= 0) {
				winflag = 2; //第二个人赢
				break;
			}
			else if(round1 >= s1->weaponNumber && round2 >= s2->weaponNumber) {
				winflag = 4; //两边都无可用武器，平局
				break;
			}
			else if(CheckState(s1, s2) == 1) {
				winflag = 4; //双方无交手，状态不变，平局 
				break;
			}
		}
		return winflag;
	}
	
	//寻找战场
	void FindCombat(Headquarter& red, Headquarter& blue, int cityNumber) {
		for(int i = 0; i <= cityNumber+1; ++i) {
			if(red.whereSoldier[i] != 0 && blue.whereSoldier[i] != 0) {
				int idr = red.whereSoldier[i]-1;
				int idb = blue.whereSoldier[i]-1;
				int winflag = 0; //战斗结果标记，1第一个人赢，2第二个人赢，3两败俱伤，4都活着
				if(i % 2 == 1) {
					winflag = Combat(red.soldierList[idr], blue.soldierList[idb]);
					if(winflag == 1) {
						cout << setw(3) << setfill('0') << times/60 << ':' << times%60 << " red " <<  red.soldierList[idr]->typeName << ' ' << idr+1 << " killed blue " << blue.soldierList[idb]->typeName << ' ' << idb+1 << " in city " << i << " remaining " << red.soldierList[idr]->hp << " elements" <<endl;
						GrabWeapon(red.soldierList[idr], blue.soldierList[idb]);
						blue.whereSoldier[i] = 0;
						delete blue.soldierList[idb];
						blue.soldierList[idb] = nullptr;
					}
					else if(winflag == 2) {
						cout << setw(3) << setfill('0') << times/60 << ':' << times%60 << " blue " <<  blue.soldierList[idb]->typeName << ' ' << idb+1 << " killed red " << red.soldierList[idr]->typeName << ' ' << idr+1 << " in city " << i << " remaining " << blue.soldierList[idb]->hp << " elements" <<endl;
						GrabWeapon(blue.soldierList[idb], red.soldierList[idr]);
						red.whereSoldier[i] = 0;
						delete red.soldierList[idr];
						red.soldierList[idr] = nullptr;
					}
					else if(winflag == 3) {
						cout << setw(3) << setfill('0') << times/60 << ':' << times%60 << " both red " <<  red.soldierList[idr]->typeName << ' ' << idr+1 << " and blue " << blue.soldierList[idb]->typeName << ' ' << idb+1 << " died in city " << i <<endl;
						red.whereSoldier[i] = 0;
						delete red.soldierList[idr];
						red.soldierList[idr] = nullptr;
						blue.whereSoldier[i] = 0;
						delete blue.soldierList[idb];
						blue.soldierList[idb] = nullptr;
					}
					else {
						CountWeaponNumber(red.soldierList[idr]);
						CountWeaponNumber(blue.soldierList[idb]);
						cout << setw(3) << setfill('0') << times/60 << ':' << times%60 << " both red " <<  red.soldierList[idr]->typeName << ' ' << idr+1 << " and blue " << blue.soldierList[idb]->typeName << ' ' << idb+1 << " were alive in city " << i <<endl;
					}
				}
				else {
					winflag = Combat(blue.soldierList[idb], red.soldierList[idr]);
					if(winflag == 2) {
						cout << setw(3) << setfill('0') << times/60 << ':' << times%60 << " red " <<  red.soldierList[idr]->typeName << ' ' << idr+1 << " killed blue " << blue.soldierList[idb]->typeName << ' ' << idb+1 << " in city " << i << " remaining " << red.soldierList[idr]->hp << " elements" <<endl;
						GrabWeapon(red.soldierList[idr], blue.soldierList[idb]);
						blue.whereSoldier[i] = 0;
						delete blue.soldierList[idb];
						blue.soldierList[idb] = nullptr;
					}
					else if(winflag == 1) {
						cout << setw(3) << setfill('0') << times/60 << ':' << times%60 << " blue " <<  blue.soldierList[idb]->typeName << ' ' << idb+1 << " killed red " << red.soldierList[idr]->typeName << ' ' << idr+1 << " in city " << i << " remaining " << blue.soldierList[idb]->hp << " elements" <<endl;
						GrabWeapon(blue.soldierList[idb], red.soldierList[idr]);
						red.whereSoldier[i] = 0;
						delete red.soldierList[idr];
						red.soldierList[idr] = nullptr;
					}
					else if(winflag == 3) {
						cout << setw(3) << setfill('0') << times/60 << ':' << times%60 << " both red " <<  red.soldierList[idr]->typeName << ' ' << idr+1 << " and blue " << blue.soldierList[idb]->typeName << ' ' << idb+1 << " died in city " << i <<endl;
						red.whereSoldier[i] = 0;
						delete red.soldierList[idr];
						red.soldierList[idr] = nullptr;
						blue.whereSoldier[i] = 0;
						delete blue.soldierList[idb];
						blue.soldierList[idb] = nullptr;
					}
					else {
						CountWeaponNumber(red.soldierList[idr]);
						CountWeaponNumber(blue.soldierList[idb]);
						cout << setw(3) << setfill('0') << times/60 << ':' << times%60 << " both red " <<  red.soldierList[idr]->typeName << ' ' << idr+1 << " and blue " << blue.soldierList[idb]->typeName << ' ' << idb+1 << " were alive in city " << i <<endl;
					}
				}
				//dragon欢呼
				if(red.soldierList[idr] != nullptr && red.soldierList[idr]->type == 0 && red.soldierList[idr]->hp > 0)
					cout << setw(3) << setfill('0') << times/60 << ':' << times%60 << " red dragon " << idr+1 << " yelled in city " << i << endl;
				if(blue.soldierList[idb] != nullptr && blue.soldierList[idb]->type == 0 && blue.soldierList[idb]->hp > 0)
					cout << setw(3) << setfill('0') << times/60 << ':' << times%60 << " blue dragon " << idb+1 << " yelled in city " << i << endl;
			}
		}
		return;
	}
	
	//武士报告自己的情况
	void SoldierReport(Headquarter& red, Headquarter& blue, int cityNumber) {
		for(int i = 0; i <= cityNumber+1; ++i) {
			if(red.whereSoldier[i] != 0) {
				int idr = red.whereSoldier[i]-1;
				cout << setw(3) << setfill('0') << times/60 << ':' << times%60 << " red " << red.soldierList[idr]->typeName << " " << idr+1 << " has " << red.soldierList[idr]->weaponClass[0] << " sword " << red.soldierList[idr]->weaponClass[1] << " bomb " << red.soldierList[idr]->weaponClass[2] << " arrow and " << red.soldierList[idr]->hp << " elements" << endl;
			}
			if(blue.whereSoldier[i] != 0) {
				int idb = blue.whereSoldier[i]-1;
				cout << setw(3) << setfill('0') << times/60 << ':' << times%60 << " blue " << blue.soldierList[idb]->typeName << " " << idb+1 << " has " << blue.soldierList[idb]->weaponClass[0] << " sword " << blue.soldierList[idb]->weaponClass[1] << " bomb " << blue.soldierList[idb]->weaponClass[2] << " arrow and " << blue.soldierList[idb]->hp << " elements" << endl;
			}
		}
		return;
	}
	
	//阵营双方开始交战
	void start() {
		int t = 0;
		cin >> t;
		for(int t0 = 1; t0 <= t; ++t0) {
			int M, N, K, T;	//司令部生命，城市数，忠诚度下降系数，截至时间
			cin >> M >> N >> K >> T;
			int hpSoldier[5];
			for(int i = 0; i < 5; cin >> hpSoldier[i++]);
			int adSoldier[5];
			for(int i = 0; i < 5; cin >> adSoldier[i++]);
			cout << "Case " << t0 << ":" << endl;
			int orderRed[5] = {2, 3, 4, 1, 0}, orderBlue[5] = {3, 0, 1, 2, 4};
			Headquarter red(M, 0, orderRed);
			Headquarter blue(M, 1, orderBlue);
			
			times = 0;
			while(times <= T) {
				red.MakeSoldier(hpSoldier,adSoldier, N, times);
				blue.MakeSoldier(hpSoldier,adSoldier, N, times);
				
				times += 5;
				if(times > T) break;
				IfLoyalty(red, blue, N);
					
				times += 5;
				if(times > T) break;
				if(SoldierGo(red, blue, K, N) == 1) break; //到达敌方司令部则跳出
				
				times += 25;
				if(times > T) break;
				WolfGrabWeapon(red, blue, N);
				
				times += 5;
				if(times > T) break;				
				FindCombat(red, blue, N);
				
				times += 10;
				if(times > T) break;				
				cout << setw(3) << setfill('0') << times/60 << ':' << times%60 << ' ' << red.hp << " elements in red headquarter" << endl;
				cout << setw(3) << setfill('0') << times/60 << ':' << times%60 << ' ' << blue.hp << " elements in blue headquarter" << endl;
				
				times += 5;
				if(times > T) break;				
				SoldierReport(red, blue, N);
				
				times += 5;
				if(times > T) break;
			}
		}
		return;
	}
};

int main() {
	CombatSystem c;
	c.start();
	return 0;
} 


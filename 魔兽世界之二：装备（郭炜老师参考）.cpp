
// by Guo Wei
#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

//下面这些东西都是常量，而且不止一个类都要用到，就声明为全局的较为简单
#define WARRIOR_NUM 5
#define WEAPON_NUM 3
enum { DRAGON, NINJA, ICEMAN, LION, WOLF };

/*

char * CWarrior::Names[WARRIOR_NUM] = { "dragon","ninja","iceman","lion","wolf" };
红方司令部按照 iceman、lion、wolf、ninja、dragon 的顺序制造武士。
蓝方司令部按照 lion、dragon、ninja、iceman、wolf 的顺序制造武士。 */

class CHeadquarter;
class CDragon;
class CNinja;
class CIceman;
class CLion;
class CWolf;
class CWeapon;
class CWarrior;

class CWeapon {
public:
    int nKindNo;
    int nForce;
    static int InitialForce[WEAPON_NUM];
    static const char* Names[WEAPON_NUM];
};

class CWarrior {
protected:
    CHeadquarter* pHeadquarter;
    int nNo;
public:
    static const char* Names[WARRIOR_NUM];
    static int InitialLifeValue[WARRIOR_NUM];
    CWarrior(CHeadquarter* p, int nNo_) :pHeadquarter(p), nNo(nNo_) { }
    virtual void PrintResult(int nTime, int nKindNo);
    virtual void PrintResult(int nTime) = 0;
    virtual ~CWarrior() { }

};

class CHeadquarter {
private:
    static const int MAX_WARRIORS = 1000;
    int nTotalLifeValue;
    bool bStopped;
    int nColor;
    int nCurMakingSeqIdx;
    int anWarriorNum[WARRIOR_NUM];
    int nTotalWarriorNum;
    CWarrior* pWarriors[MAX_WARRIORS];
public:
    friend class CWarrior;
    static int MakingSeq[2][WARRIOR_NUM];
    void Init(int nColor_, int lv);
    ~CHeadquarter();
    int Produce(int nTime);
    void GetColor(char* szColor);
    int GetTotalLifeValue() { return nTotalLifeValue; }
};

void CWarrior::PrintResult(int nTime, int nKindNo) {
    char szColor[20];
    pHeadquarter->GetColor(szColor);
    printf("%03d %s %s %d born with strength %d,%d %s in %s headquarter\n"
        , nTime, szColor, Names[nKindNo], nNo, InitialLifeValue[nKindNo],
        pHeadquarter->anWarriorNum[nKindNo], Names[nKindNo], szColor);

}

class CDragon :public CWarrior {
private:
    CWeapon wp;
    double fmorale;
public:
    void Countmorale() {
        fmorale = pHeadquarter->GetTotalLifeValue() / (double)CWarrior::InitialLifeValue[0];
    }
    CDragon(CHeadquarter* p, int nNo_) :CWarrior(p, nNo_) {
        wp.nKindNo = nNo % WEAPON_NUM;
        wp.nForce = CWeapon::InitialForce[wp.nKindNo];
        Countmorale();
    }
    void PrintResult(int nTime) {
        CWarrior::PrintResult(nTime, DRAGON);
        printf("It has a %s,and it's morale is %.2f\n", CWeapon::Names[wp.nKindNo], fmorale);
    }
};

class CNinja :public CWarrior {
private:
    CWeapon wps[2];
public:
    CNinja(CHeadquarter* p, int nNo_) :CWarrior(p, nNo_) {
        wps[0].nKindNo = nNo % WEAPON_NUM;
        wps[0].nForce = CWeapon::InitialForce[wps[0].nKindNo];
        wps[1].nKindNo = (nNo + 1) % WEAPON_NUM;
        wps[1].nForce = CWeapon::InitialForce[wps[1].nKindNo];
    }
    void PrintResult(int nTime) {
        CWarrior::PrintResult(nTime, NINJA);
        printf("It has a %s and a %s\n", CWeapon::Names[wps[0].nKindNo], CWeapon::Names[wps[1].nKindNo]);
    }

};

class CIceman :public CWarrior {
private:
    CWeapon wp;
public:
    CIceman(CHeadquarter* p, int nNo_) :CWarrior(p, nNo_) {
        wp.nKindNo = nNo % WEAPON_NUM;
        wp.nForce = CWeapon::InitialForce[wp.nKindNo];

    }

    void PrintResult(int nTime) {
        CWarrior::PrintResult(nTime, ICEMAN);
        printf("It has a %s\n", CWeapon::Names[wp.nKindNo]);
    }

};

class CLion :public CWarrior {
private:
    int nLoyalty;
public:
    void CountLoyalty() {
        nLoyalty = pHeadquarter->GetTotalLifeValue();
    }
    CLion(CHeadquarter* p, int nNo_) :CWarrior(p, nNo_) { CountLoyalty(); }
    void PrintResult(int nTime) {
        CWarrior::PrintResult(nTime, LION);
        CountLoyalty();
        printf("It's loyalty is %d\n", nLoyalty);
    }

};

class CWolf :public CWarrior {
public:
    CWolf(CHeadquarter* p, int nNo_) :CWarrior(p, nNo_) { }
    void PrintResult(int nTime) {
        CWarrior::PrintResult(nTime, WOLF);
    }
};

void CHeadquarter::Init(int nColor_, int lv) {
    nColor = nColor_;
    nTotalLifeValue = lv;
    bStopped = false;
    nCurMakingSeqIdx = 0;
    nTotalWarriorNum = 0;

    for (int i = 0; i < WARRIOR_NUM; i++) anWarriorNum[i] = 0;

}

CHeadquarter::~CHeadquarter() {
    int i;
    for (i = 0; i < nTotalWarriorNum; i++)  delete pWarriors[i];

}
int CHeadquarter::Produce(int nTime) {

    int nSearchingTimes = 0;
    if (bStopped)
        return 0;
    while (CWarrior::InitialLifeValue[MakingSeq[nColor][nCurMakingSeqIdx]]
    > nTotalLifeValue && nSearchingTimes < WARRIOR_NUM)
    {
        nCurMakingSeqIdx = (nCurMakingSeqIdx + 1) % WARRIOR_NUM;
        nSearchingTimes++;
    }

    int nKindNo = MakingSeq[nColor][nCurMakingSeqIdx];
    if (CWarrior::InitialLifeValue[nKindNo] > nTotalLifeValue) {
        bStopped = true;
        if (nColor == 0)
            printf("%03d red headquarter stops making warriors\n", nTime);
        else
            printf("%03d blue headquarter stops making warriors\n", nTime);
        return 0;

    }
    nTotalLifeValue -= CWarrior::InitialLifeValue[nKindNo];
    nCurMakingSeqIdx = (nCurMakingSeqIdx + 1) % WARRIOR_NUM;
    int nTmp = anWarriorNum[nKindNo];
    anWarriorNum[nKindNo]++;
    switch (nKindNo) {
    case DRAGON:
        pWarriors[nTotalWarriorNum] = new CDragon(this, nTotalWarriorNum + 1);
        break;
    case NINJA:
        pWarriors[nTotalWarriorNum] = new CNinja(this, nTotalWarriorNum + 1);
        break;
    case ICEMAN:
        pWarriors[nTotalWarriorNum] = new CIceman(this, nTotalWarriorNum + 1);
        break;
    case LION:
        pWarriors[nTotalWarriorNum] = new CLion(this, nTotalWarriorNum + 1);
        break;
    case WOLF:
        pWarriors[nTotalWarriorNum] = new CWolf(this, nTotalWarriorNum + 1);
        break;
    }

    pWarriors[nTotalWarriorNum]->PrintResult(nTime);
    nTotalWarriorNum++;
    return 1;

}

void CHeadquarter::GetColor(char* szColor) {

    if (nColor == 0)
        strcpy(szColor, "red");
    else
        strcpy(szColor, "blue");
}

const char* CWeapon::Names[WEAPON_NUM] = { "sword","bomb","arrow" };
int CWeapon::InitialForce[WEAPON_NUM];
const char* CWarrior::Names[WARRIOR_NUM] = { "dragon","ninja","iceman","lion","wolf" };
int CWarrior::InitialLifeValue[WARRIOR_NUM];

int CHeadquarter::MakingSeq[2][WARRIOR_NUM] = { { 2,3,4,1,0 },{3,0,1,2,4} };

int main() {

    int t;
    int m;
    //freopen("war2.in","r",stdin);
    CHeadquarter RedHead, BlueHead;
    scanf("%d", &t);
    int nCaseNo = 1;
    while (t--) {
        printf("Case:%d\n", nCaseNo++);
        scanf("%d", &m);
        int i;
        for (i = 0; i < WARRIOR_NUM; i++)
            scanf("%d", &CWarrior::InitialLifeValue[i]);
        RedHead.Init(0, m);
        BlueHead.Init(1, m);
        int nTime = 0;
        while (true) {
            int tmp1 = RedHead.Produce(nTime);
            int tmp2 = BlueHead.Produce(nTime);
            if (tmp1 == 0 && tmp2 == 0) break;
            nTime++;
        }
    }
    return 0;
}
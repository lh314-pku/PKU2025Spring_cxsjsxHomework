#include <iostream>
#include <string>
#include <map>
#include <cmath>

using namespace std;
typedef multimap<int, int> mmii;

int main()
{
    mmii boxingmap;
    mmii::iterator p1, p2, ret;
    string func;
    int opernumbers, id, attack, temp1, temp2, tempname;
    cin >> opernumbers;
    boxingmap.insert(make_pair(1000000000, 1));
    while (opernumbers--)
    {
        cin >> id >> attack;
        p1 = boxingmap.lower_bound(attack);
        if (p1 == boxingmap.begin())
            ret = p1;
        else
        {
            p2 = p1--;
            temp1 = abs(p1->first - attack), temp2 = abs(p2->first - attack);
            if (temp2 < temp1)   ret = p2;
            else if (temp1 < temp2) ret = p1;
            else ret = (p1->second < p2->second ? p1 : p2);
        }
        tempname = ret->second;
        cout << id << ' ' << tempname << endl;
        if (ret->first != attack)
            boxingmap.insert(make_pair(attack, id));
        else
            ret->second = (id < tempname ? id : tempname);
    }
    return 0;
}

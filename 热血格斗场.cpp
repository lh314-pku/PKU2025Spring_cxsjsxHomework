#include <iostream>
#include <set>
#include <cmath>

using namespace std;

struct Member {
    int strength; // 实力值
    int id;       // 用户 ID

    bool operator<(const Member& other) const {
        if (strength == other.strength) {
            return id < other.id;
        }
        return strength < other.strength;
    }
};

int main() {
    int n;
    cin >> n;

    set<Member> members;
    members.insert({ 1000000000, 1 });

    for (int i = 0; i < n; ++i) {
        int id, strength;
        cin >> id >> strength;

        auto it = members.lower_bound({ strength, 0 });

        int matchId;
        if (it == members.begin()) {
            matchId = it->id;
        }
        else {
            auto prevIt = prev(it);
            if (it == members.end() ||
                abs(prevIt->strength - strength) <= abs(it->strength - strength)) {
                matchId = prevIt->id;
            }
            else {
                matchId = it->id;
            }
        }

        cout << id << " " << matchId << endl;

        members.insert({ strength, id });
    }

    return 0;
}

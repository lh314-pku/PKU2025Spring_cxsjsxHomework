#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n; // 读取命令数量
    unordered_map<int, vector<int>> seqs; // 用于存储每个序列，键为id

    while (n--) {
        string cmd;
        cin >> cmd;

        if (cmd == "new") {
            int id;
            cin >> id;
            if (id < 10000) {
                seqs[id] = vector<int>(); // 创建一个新的序列
            }

        } else if (cmd == "add") {
            int id, num;
            cin >> id >> num;
            if (seqs.find(id) != seqs.end()) {
                seqs[id].push_back(num); // 往指定id序列中添加数字
            }

        } else if (cmd == "merge") {
            int id1, id2;
            cin >> id1 >> id2;
            if (id1 != id2 && seqs.find(id1) != seqs.end() && seqs.find(id2) != seqs.end()) {
                seqs[id1].insert(seqs[id1].end(), seqs[id2].begin(), seqs[id2].end()); // 将id2合并到id1
                seqs[id2].clear(); // 清空id2
            }

        } else if (cmd == "unique") {
            int id;
            cin >> id;
            if (seqs.find(id) != seqs.end()) {
                vector<int> &seq = seqs[id];
                set<int> seen;
                vector<int> new_seq;

                for (int num : seq) {
                    if (seen.find(num) == seen.end()) {
                        new_seq.push_back(num); // 只保留没有见过的数字
                        seen.insert(num);
                    }
                }

                seq = new_seq; // 更新序列为去重后的序列
            }

        } else if (cmd == "out") {
            int id;
            cin >> id;
            if (seqs.find(id) != seqs.end()) {
                vector<int> seq = seqs[id];
                sort(seq.begin(), seq.end()); // 从小到大排序
                for (size_t i = 0; i < seq.size(); i++) {
                    if (i > 0) cout << " ";
                    cout << seq[i];
                }
                cout << endl;
            }
        }
    }

    return 0;
}
// 其实也可以用<list>解决
// 但是，list在遍历的时间复杂度高于vector
// 不便于去重
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cctype>
#include <algorithm>

using namespace std;

// 辅助函数：判断字符串是否为数字
bool isInteger(const string &str) {
    if (str.empty()) return false;
    for (char c : str) {
        if (!isdigit(c)) return false;
    }
    return true;
}

// copy 操作
string copy(const string &s, int x, int l) {
    return s.substr(x, l);
}

// add 操作
string add(const string &s1, const string &s2) {
    if (isInteger(s1) && isInteger(s2)) {
        // 转换为整数做加法
        int num1 = stoi(s1);
        int num2 = stoi(s2);
        return to_string(num1 + num2);
    }
    // 字符串连接
    return s1 + s2;
}

// find 操作
int find(const string &s, const string &sub) {
    size_t pos = s.find(sub);
    return pos == string::npos ? s.size() : pos;
}

// rfind 操作
int rfind(const string &s, const string &sub) {
    size_t pos = s.rfind(sub);
    return pos == string::npos ? s.size() : pos;
}

// insert 操作
void insert(string &target, const string &s, int pos) {
    target.insert(pos, s);
}

// reset 操作
void reset(string &target, const string &s) {
    target = s;
}

// parseNumber：解析数字表达式
int parseNumber(const string &exp, const vector<string> &strings);

// parseString：解析字符串表达式
string parseString(const string &exp, const vector<string> &strings) {
    // 如果是 copy 表达式
    if (exp.substr(0, 4) == "copy") {
        stringstream ss(exp.substr(5));
        int n, x, l;
        ss >> n >> x >> l;
        const string &target = strings[n - 1];
        x = parseNumber(to_string(x), strings);
        l = parseNumber(to_string(l), strings);
        return copy(target, x, l);
    }

    // 如果是 add 表达式
    if (exp.substr(0, 3) == "add") {
        stringstream ss(exp.substr(4));
        string s1, s2;
        ss >> s1 >> s2;
        s1 = parseString(s1, strings);
        s2 = parseString(s2, strings);
        return add(s1, s2);
    }

    // 直接返回字符串
    return exp;
}

// parseNumber：解析数字表达式
int parseNumber(const string &exp, const vector<string> &strings) {
    // 如果是 find 表达式
    if (exp.substr(0, 4) == "find") {
        stringstream ss(exp.substr(5));
        string s;
        int n;
        ss >> s >> n;
        s = parseString(s, strings);
        n = parseNumber(to_string(n), strings);
        const string &target = strings[n - 1];
        return find(target, s);
    }

    // 如果是 rfind 表达式
    if (exp.substr(0, 5) == "rfind") {
        stringstream ss(exp.substr(6));
        string s;
        int n;
        ss >> s >> n;
        s = parseString(s, strings);
        n = parseNumber(to_string(n), strings);
        const string &target = strings[n - 1];
        return rfind(target, s);
    }

    // 直接把字符串转成整数
    return stoi(exp);
}

int main() {
    int n;
    cin >> n;
    vector<string> strings(n);

    // 输入字符串
    for (int i = 0; i < n; ++i) {
        cin >> strings[i];
    }

    string command;
    while (cin >> command) {
        if (command == "over") {
            break;
        } else if (command == "insert") {
            string s, exp;
            int N, X;
            cin >> s >> exp >> X;
            N = parseNumber(exp, strings);
            const string &target = strings[N - 1];
            X = parseNumber(to_string(X), strings);
            insert(strings[N - 1], parseString(s, strings), X);
        } else if (command == "reset") {
            string s, exp;
            int N;
            cin >> s >> exp;
            N = parseNumber(exp, strings);
            reset(strings[N - 1], parseString(s, strings));
        } else if (command == "print") {
            int N;
            cin >> N;
            cout << strings[N - 1] << endl;
        } else if (command == "printall") {
            for (const string &s : strings) {
                cout << s << endl;
            }
        }
    }

    return 0;
}
 
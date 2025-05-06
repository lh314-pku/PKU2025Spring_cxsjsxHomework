#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cctype>
#include <cstdlib>
using namespace std;

vector<string> strs;

int findStr(const string& s, const string& content, bool reverse) {
    if (reverse) {
        size_t pos = content.rfind(s);
        return pos == string::npos ? content.length() : pos;
    } else {
        size_t pos = content.find(s);
        return pos == string::npos ? content.length() : pos;
    }
}

bool isInteger(const string& s) {
    for (char c : s) {
        if (!isdigit(c)) return false;
    }
    return true && !s.empty();
}

string evalExpression(const string& expr);

string processAdd(const string& S1, const string& S2) {
    string left = evalExpression(S1);
    string right = evalExpression(S2);
    if (isInteger(left) && isInteger(right)) {
        int result = stoi(left) + stoi(right);
        return to_string(result);
    } else {
        return left + right;
    }
}

string processCopy(int n, int x, int l) {
    return strs[n - 1].substr(x, l);
}

int processFind(string s, int n, bool reverse) {
    string target = evalExpression(s);
    return findStr(target, strs[n - 1], reverse);
}

void processCommands(const string& command);

string evalExpression(const string& expr) {
    stringstream ss(expr);
    string token;
    ss >> token;

    if (token == "copy") {
        int n, x, l;
        ss >> n >> x >> l;
        return processCopy(n, x, l);
    } else if (token == "add") {
        string S1, S2;
        ss >> S1 >> S2;
        return processAdd(S1, S2);
    } else {
        return token; // raw string
    }
}

void processCommands(const string& command) {
    stringstream ss(command);
    string op;
    ss >> op;

    if (op == "print") {
        int n; ss >> n;
        cout << strs[n - 1] << endl;
    } else if (op == "printall") {
        for (const string& str : strs) {
            cout << str << endl;
        }
    } else if (op == "insert") {
        string S; int n, x;
        ss >> S >> n >> x;
        string toInsert = evalExpression(S);
        strs[n - 1].insert(x, toInsert);
    } else if (op == "reset") {
        string S; int n;
        ss >> S >> n;
        strs[n - 1] = evalExpression(S);
    } else if (op == "find") {
        string S; int n;
        ss >> S >> n;
        cout << processFind(S, n, false) << endl;
    } else if (op == "rfind") {
        string S; int n;
        ss >> S >> n;
        cout << processFind(S, n, true) << endl;
    } else if (op == "over") {
        return;
    }
}

int main() {
    int n;
    cin >> n;
    cin.ignore();

    strs.resize(n);
    for (int i = 0; i < n; ++i) {
        getline(cin, strs[i]);
    }

    string command;
    while (getline(cin, command)) {
        if (command == "over") break;
        processCommands(command);
    }

    return 0;
}

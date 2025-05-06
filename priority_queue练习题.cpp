#include <iostream>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;

// 计算质因数数目（不包括自身）
int countPrimeFactors(int n) {
    int count = 0;
    for (int i = 2; i <= sqrt(n); ++i) {
        if (n % i == 0) {
            count++;
        }
        while (n % i == 0) {
            n /= i;
        }
    }
    if (n > 1 && count != 0) {
        count++; // 如果最后剩下的n是质数，也计算一次
    }
    return count;
}

// 最大优先级比较函数
struct MaxCompare {
    bool operator()(int a, int b) {
        int countA = countPrimeFactors(a);
        int countB = countPrimeFactors(b);
        // cout << a << ":" << countA << "," << b <<":" << countB << endl;
        if (countA != countB) {
            return countA < countB; // 质因数数目多的优先级高
        }
        return a < b; // 质因数数目相同时，数值大的优先级高
    }
};

// 最小优先级比较函数
struct MinCompare {
    bool operator()(int a, int b) {
        int countA = countPrimeFactors(a);
        int countB = countPrimeFactors(b);
        if (countA != countB) {
            return countA > countB; // 质因数数目少的优先级高
        }
        return a > b; // 质因数数目相同时，数值小的优先级高
    }
};

int main() {
    int num;
    cin >> num; // 添加元素的次数

    priority_queue<int, vector<int>, MaxCompare> maxQueue;
    priority_queue<int, vector<int>, MinCompare> minQueue;

    for (int i = 0; i < num; ++i) {
        // 每次添加10个元素
        for (int j = 0; j < 10; ++j) {
            int n;
            cin >> n;
            maxQueue.push(n);
            minQueue.push(n);
        }

        // 取出优先级最高和最低的元素
        int maxElement = maxQueue.top();
        int minElement = minQueue.top();
        maxQueue.pop();
        minQueue.pop();

        // 输出结果
        cout << maxElement << ' ' << minElement << endl;
    }

    return 0;
}
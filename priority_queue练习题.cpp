#include <algorithm>
#include <iostream>
#include <queue>
using namespace std;
bool iszhishu(int n){
    for(int i = 2; i < n; i++){
        if(n % i == 0){
            return false;
        }
    }
    return true;
}
int numofzhiyinshu(int n){
    int result = 0;
    while(n % 2 == 0){
        result++;
        n = n / 2;
    }
    for(int i = 3; i < n && iszhishu(i); i=i+1){
        while(n % i == 0){
            result++;
            n = n / i;
        }
    }
    cout << n << " " << result << endl;
    return result;
}

class cmp{
public:
    bool operator()(int a, int b){
        return(numofzhiyinshu(a) < numofzhiyinshu(b));
    }
};
int main(){
    int n = 0;
    cin >> n;
    while(n--){
        priority_queue<int, vector<int>, cmp> pq;
        for(int i = 0; i < 10; i++){
            int a = 0;
            cin >> a;
            pq.push(a);
        }
        for(int i = 0; i < 10; i++){
            if(i == 0){
                cout << pq.top() << " ";
            }
            if(i == 9){
                cout << pq.top() << " ";
            }
            pq.pop();
        }
    }
    return 0;
}
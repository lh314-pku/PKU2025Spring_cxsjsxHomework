#include <iostream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;
struct Fighter{
    int id;
    int power;
};
int distance(Fighter a, Fighter b){
    return abs(a.power - b.power);
}
int main(){

    return 0;
}
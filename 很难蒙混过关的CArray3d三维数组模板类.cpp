#include <iostream>
#include <iomanip> 
#include <cstring>
using namespace std;
template <class T>
class CArray3D
{
// 在此处补充你的代码
public:
    // 先构造二维数组，而三维数组由二维数组的数组生成
    class CArray2D{
        private:
            T* data;
            int Y, Z;
        public:
            CArray2D():data(nullptr),Y(0),Z(0){}
            ~CArray2D(){
                delete[] data;
            }
            void allocate(int y, int z) {
                Y = y; Z = z;
                data = new T[Y * Z]();
            }
            T* operator[](int y) {
                return data + y * Z;
            }
            const T* operator[](int y) const {
                return data + y * Z;
            }
            operator T*(){
                return data;
            }
    };
private:
    CArray2D* carray2D;
    int X;
public:
    CArray3D(int x, int y, int z):X(x){
        carray2D = new CArray2D[X];
        for(int i = 0; i < X; i++){
            carray2D[i].allocate(y, z);
        }
    }
    ~CArray3D(){
        delete[] carray2D;
    }
    CArray2D& operator[](int x) {
		return carray2D[x];
	}
	
	const CArray2D& operator[](int x) const {
		return carray2D[x];
	}
};

CArray3D<int> a(3,4,5);
CArray3D<double> b(3,2,2);
void PrintA()
{
	for(int i = 0;i < 3; ++i) {
		cout << "layer " << i << ":" << endl;
		for(int j = 0; j < 4; ++j) {
			for(int k = 0; k < 5; ++k) 
				cout << a[i][j][k] << "," ;
			cout << endl;
		}
	}
}
void PrintB()
{
	for(int i = 0;i < 3; ++i) {
		cout << "layer " << i << ":" << endl;
		for(int j = 0; j < 2; ++j) {
			for(int k = 0; k < 2; ++k) 
				cout << b[i][j][k] << "," ;
			cout << endl;
		}
	}
}

int main()
{

	int No = 0;
	for( int i = 0; i < 3; ++ i ) {
		a[i];
		for( int j = 0; j < 4; ++j ) {
			a[j][i];
			for( int k = 0; k < 5; ++k )
				a[i][j][k] = No ++;
			a[j][i][i];	
		}
	}
	PrintA();
	memset(a[1],-1 ,20*sizeof(int));	
	memset(a[1],-1 ,20*sizeof(int));
	PrintA(); 
	memset(a[1][1],0 ,5*sizeof(int));	
	PrintA();

	for( int i = 0; i < 3; ++ i )
		for( int j = 0; j < 2; ++j )
			for( int k = 0; k < 2; ++k )
				b[i][j][k] = 10.0/(i+j+k+1);
	PrintB();
	int n = a[0][1][2];
	double f = b[0][1][1];
	cout << "****" << endl;
	cout << n << "," << f << endl;
		
	return 0;
}
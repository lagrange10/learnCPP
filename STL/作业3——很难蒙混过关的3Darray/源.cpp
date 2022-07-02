#include <iostream>
#include <iomanip> 
#include <cstring>
using namespace std;
template <class T>
class CArray3D
{
	// 在此处补充你的代码
private:
	int layer;
	int row;
	int col;
	T* p;
public:
	// ---------------------内部类CArray2D-----------------------
	//这个内部类是用来表达CArray3D的每一层的内容的，因此T* p所指的内容是CArray3D中的东西
	template <class T>
	class CArray2D
	{
	private:
		int row;
		int col;
		T* p;
	public:
		CArray2D(T* p, int r, int c) : p(p), row(r), col(c)
		{
			
		}
		virtual ~CArray2D()
		{
			//一定不要析构！！！
		}
		T* operator[](int row)
		{
			return p + row * col;
		}
		friend class CArray3D;
		operator void* ()
		{
			return p;
		}
	};
	// ---------------------内部类CArray2D结束------------------

	CArray3D(int l,int r,int c):layer(l), row(r), col(c) 
	{
		p = new T[l * r * c];
	}
	virtual ~CArray3D()
	{
		delete[] p;
	}
	CArray2D<T> operator[](int layer)
	{
		return CArray2D<T>(p + layer * row * col, row, col);
	}
};

CArray3D<int> a(3, 4, 5);
CArray3D<double> b(3, 2, 2);
void PrintA()
{
	for (int i = 0; i < 3; ++i) {
		cout << "layer " << i << ":" << endl;
		for (int j = 0; j < 4; ++j) {
			for (int k = 0; k < 5; ++k)
				cout << a[i][j][k] << ",";
			cout << endl;
		}
	}
}
void PrintB()
{
	for (int i = 0; i < 3; ++i) {
		cout << "layer " << i << ":" << endl;
		for (int j = 0; j < 2; ++j) {
			for (int k = 0; k < 2; ++k)
				cout << b[i][j][k] << ",";
			cout << endl;
		}
	}
}

int main()
{

	int No = 0;
	for (int i = 0; i < 3; ++i) {
		a[i];
		for (int j = 0; j < 4; ++j) {
			a[j][i];
			for (int k = 0; k < 5; ++k)
				a[i][j][k] = No++;
			a[j][i][i];
		}
	}
	PrintA();
	memset(a[1], -1, 20 * sizeof(int));
	memset(a[1], -1, 20 * sizeof(int));
	PrintA();
	memset(a[1][1], 0, 5 * sizeof(int));
	PrintA();

	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 2; ++j)
			for (int k = 0; k < 2; ++k)
				b[i][j][k] = 10.0 / (i + j + k + 1);
	PrintB();
	int n = a[0][1][2];
	double f = b[0][1][1];
	cout << "****" << endl;
	cout << n << "," << f << endl;

	return 0;
}
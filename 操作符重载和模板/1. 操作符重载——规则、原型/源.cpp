#include <iostream>
using namespace std;

class Integer
{
private:
	int i;
public:
	Integer() :i(0) {}
	Integer(int ii):i(ii){}
	virtual ~Integer() {}

	//binary operator
	friend const Integer operator+(const Integer& l, const Integer& r); 
	friend const Integer& operator+=(Integer& l, const Integer& r);
	//unary operator
	const Integer& operator++()  //prefix++
	{ 
		*this += 1; 
		return *this; //直接用自己的引用，比较「环保」。 i.e. return const T&;
	} 

	const Integer operator++(int)  //postfix++
	{ 
		Integer old(i);
		*this += 1;
		return old;   //局部变量，千万不要传出一个引用。 i.e. return const T;
	} 

	//关系运算符
	friend bool operator==(const Integer& l, const Integer& r);
	friend bool operator<(const Integer& l, const Integer& r);
	friend bool operator>(const Integer& l, const Integer& r);
	friend ostream& operator<<(ostream& out, const Integer& i);

	void print() { cout << i << endl; }
};

//成员vs非成员
//单目和一些特殊的运算符(=,->,->*,()应该或者必须是成员)
//其它二元运算符应该是非成员
const Integer operator+(const Integer& l, const Integer& r)
{
	return Integer(l.i + r.i);
}

const Integer& operator+=(Integer& l, const Integer& r)
{
	l.i += r.i;
	return l;
}

bool operator==(const Integer& l, const Integer& r)
{
	return l.i == r.i;
}

bool operator<(const Integer& l, const Integer& r)
{
	return l.i < r.i;
}

//cout是ostream类的对象，在iostream中已定义。返回cout本身，以进行连续的输出。
ostream& operator<<(ostream& out, const Integer& i)
{
	out << i.i << endl;
	return out;
}

//法则，永远用以前定义过的函数
bool operator>(const Integer& l, const Integer& r)
{
	return r < l;
}

class Vector
{
private:
	int* a;
	int size;
public:
	Vector(int size) :size(size) { a = new int[size]; }
	virtual ~Vector() { delete a; }
	int& operator[](int x) { return a[x]; }
};



int& test()
{
	int x = 3;
	cout << "in func, x is at " << &x << endl;
	return x;
}

void test_return_reference()
{
	int* px = &test();
	cout << "out func, x is at i.e. px = " << px << endl;
	int t;
	cout << "out func, t is at " << &t << endl;
	cout << "*px = " << *px << endl;
	*px = 13;
	cout << "modify *px = " << *px << endl;
}

void printDivide()
{
	cout << "-------------------------------------" << endl;
}

int main()
{
	cout << "双目运算，加减" << endl;
	//+,+=
	Integer x(2), y(3),z;
	z = x + y;
	z.print();
	x += Integer(6);
	x.print();
	//+类型转换
	x = 2;
	z = x + 3; cout << z;
	z = 2 + x; cout << z; //global operator overload
	z = 2 + 3; cout << z;

	printDivide();
	cout << "自增运算" << endl;
	//y=3
	cout << "初始 y = 3" << endl;
	Integer s = ++y;
	cout << "y = "; y.print();
	cout << "s = ++y = "; s.print();

	cout << endl;
	//x=8
	cout << "初始 x = 8" << endl;
	Integer t = x++;
	cout << "x = "; x.print();
	cout << "t = x++ = "; t.print();
	printDivide();

	cout << (Integer(3) > Integer(4)) << endl;
	cout << (Integer(5) < Integer(4)) << endl;

	printDivide();
	cout << "test for []" << endl;
	Vector v(10);
	for (int i = 0; i < 10; i++)
	{
		v[i] = i;
	}
	for (int i = 0; i < 10; i++)
	{
		cout << v[i] << " ";
	}
	//test_return_reference();
	return 0;
}
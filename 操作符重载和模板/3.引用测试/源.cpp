#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

class Test
{
public:
	Test();
	~Test();
	static void test_reference1()
	{
		//test for binding and assignment

		int a=1,b=2;
		int& x = a; //binding
		cout << "a = " << a << "; " << "x = " << x << "; " << "b = " << b << endl;
		printf("a at %p; x at %p\n", &a, &x);
		x = b; //assignment
		cout << "a = " << a << "; " << "x = " << x << "; " << "b = " << b << endl;
		printf("b at %p; x at %p\n", &b, &x);
	}
private:

};

Test::Test()
{
}

Test::~Test()
{
}

int main()
{
	Test::test_reference1();
}
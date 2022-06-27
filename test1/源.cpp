#include <iostream>
using namespace std;

class A
{
	int i;
public:
	A() :i(0) { cout << "consturcor a" << endl; }
};

A a[10];

int main()
{
	A a[10];
}
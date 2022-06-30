#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include "A.h"
using namespace std;

int main()
{
	A a1(1), a2;
	cout << &a1 << " " << &a2 << endl;
	cout << a1.i << " " << a2.i << endl;
	a2 = a1;
	cout << &a1 << " " << &a2 << endl;
	cout << a1.i << " " << a2.i << endl;
}

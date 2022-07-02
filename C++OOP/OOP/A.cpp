#include "A.h"
#include <iostream>

void A::seti(int i)
{
	this->i = 5;
}

int A::geti() const
{
	return i;
}

A::A(int i):i(i) {}

void A::f()
{
	std::cout << "A::f()" << std::endl;
}

void A::f()const
{
	std::cout << "A::f() const" << std::endl;
}

void A::print_arr() const
{
	std::cout << size1 << " " << size2 << std::endl;
	std::cout << a[0] << " " << b[0] << std::endl;
}
#include <iostream>
#include "A.h"
A::A() :i(0) {}

A::A(int i):i(i) 
{
	std::cout << "the constructor A::A(int a)" << std::endl;
}

A::~A() {}

A::A(const A& a)
{
	std::cout << "the copy constructor A::A(const A& a)" << std::endl;
}
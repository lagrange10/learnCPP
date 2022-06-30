#pragma once
class A
{
public:
	int i;
public:
	A();
	A(int i);
	virtual ~A();
	A(const A& a);
};


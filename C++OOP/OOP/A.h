#pragma once
class A
{
	int i;
	//���ֶ��峣���ķ���
	static const int size1 = 10;
	enum {size2 = 11};
	int a[size1],b[size2];
public:
	A(int i);
	void seti(int i);
	int geti() const;
	void f();
	void f() const;
	void print_arr() const;
};


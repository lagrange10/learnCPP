#include <iostream>
#include <string>
using namespace std;

class A
{
public:
	int i;
public:
	A():i(10) {}
	virtual void f() { cout << "A:f() i=" << i << endl; }
};

class B :public A
{
public:
	int v;
public:
	B():v(20) {}
	virtual void f() { cout << "B:f() i=" << i << "v=" << v << endl; }
};

void test_vptr()
{
	A a,aa;
	B b;
	int* p = (int*)&a;
	int* q = (int*)&aa;
	cout << *p << " " << *q << endl; //vptr是属于类的
	p++;
	cout << *p << endl;

	p = (int*)&b; //可以看出vptr指向的地方不同
	cout << *p << endl;
	p++;
	cout << *p << endl;

}

void test_copy_constructor()
{
	A a;
	B b;
	a = b; //发生什么？
	a.f(); //调用的还是a的f
	//vptr不会被拷贝，只有子类B中「适合父类A的部分」会被拷贝
	
	//指针的话 就完全是另一个地址了
	A* pa = new A;
	B* pb = new B;
	pa = pb;
	pa->f();

	//引用也是
	A& aa = b; //把B类看做A类
	aa.f();

	pa = &a;
	int* p = (int*)&a;
	int* q = (int*)&b;
	cout << *p << " " << *q << endl; 
	*p = *q;
	cout << *p << " " << *q << endl; //vptr是属于类的
	pa->f();
	a.f(); //为啥强行改了a的vptr还是调用了A类的f呢？
}


int main()
{
	//test_vptr();
	test_copy_constructor();
}
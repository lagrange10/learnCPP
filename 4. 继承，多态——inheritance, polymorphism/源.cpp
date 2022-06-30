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
	cout << *p << " " << *q << endl; //vptr���������
	p++;
	cout << *p << endl;

	p = (int*)&b; //���Կ���vptrָ��ĵط���ͬ
	cout << *p << endl;
	p++;
	cout << *p << endl;

}

void test_copy_constructor()
{
	A a;
	B b;
	a = b; //����ʲô��
	a.f(); //���õĻ���a��f
	//vptr���ᱻ������ֻ������B�С��ʺϸ���A�Ĳ��֡��ᱻ����
	
	//ָ��Ļ� ����ȫ����һ����ַ��
	A* pa = new A;
	B* pb = new B;
	pa = pb;
	pa->f();

	//����Ҳ��
	A& aa = b; //��B�࿴��A��
	aa.f();

	pa = &a;
	int* p = (int*)&a;
	int* q = (int*)&b;
	cout << *p << " " << *q << endl; 
	*p = *q;
	cout << *p << " " << *q << endl; //vptr���������
	pa->f();
	a.f(); //Ϊɶǿ�и���a��vptr���ǵ�����A���f�أ�
}


int main()
{
	//test_vptr();
	test_copy_constructor();
}
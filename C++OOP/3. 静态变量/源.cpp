#include <iostream>
#include <string>
#include <list>
#include <algorithm>
using namespace std;

class A
{
public:
	static int i;
};

class B:public A
{

};

int A::i = 1;
//int B::i=2; //����������̬

int main()
{
	B::i = 2;
	cout << A::i << " " << B::i << endl; //����2�ˡ���ȷʵ�ǹ����
	
}
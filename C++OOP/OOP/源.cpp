#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include "A.h"
using namespace std;

void MyPrintf(const char* p);
//const ����ͨ��������޸�
void test1_const()
{
	int* ip;
	const int* cip;
	int i = 5;
	ip = &i;
	cip = &i;
	*ip = 10;
	//*cip = 15; //����ͨ��cip�޸�i��ֵ

	const int ci = 3;
	//ip = &ci; //�����˶Գ����ı���������
	ip = (int*)&ci; //��ǿ������ת������
	cip = &ci; //û����

	MyPrintf("giao");
}

//const����;
//1. ϣ���ں����ڲ����޸�ָ��ָ�������
void MyPrintf(const char* p)
{
	//strcpy((char *)p, "this"); //�������޸ģ�����ƭ��������Ҳ���쳣
	puts(p);
}
//2.const���� �� const���κ��������������޸ĵĶ���
/* 1������������const����ָ���������data���ܱ��޸ģ����������
������Ҫ����ִ�е�,��������֪�������ľ���ʵ�֣���α�֤�ڲ����ݲ����޸ģ�const��*/
/* 2��const���εĺ������Թ���overload�Ĺ�ϵ��
��Ϊ��������һ���ǡ�A* this�� һ���ǡ�const A* this��*/
/* 3������������const�ı���һ��Ҫ��ʼ����ʱ���һ��ֵ��
*/

void test2_const()
{
	const A ca(1);
	cout << ca.geti() << endl;
	//ca.seti()���ܱ����ã���������ֻ�ܵ��ó���������
	A a(1);
	a.seti(5);
	cout << a.geti() << endl;
	//���ǳ����Ķ������й��з��������Ե���
	ca.f();
	a.f();
	ca.print_arr();
}


void test1_reference()
{
	//���õ�ԭ��
	//1.һ�������ñ������������ǡ��������͡����ʽ����
	int i=1,j=2;
	const int ci=3;
	//int& x = ci; //�����ƻ��˱������� const int &x = ci;�ǿ��Ե�
	//int& x = 3; //���󣡲������Ǳ��ʽ
	int& x = i;
	//2.���ô�ʼ����ֻ������һ������,�������ñ�����
}

int main()
{
	test2_const();
	//test1_reference();
}
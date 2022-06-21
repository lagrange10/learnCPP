#include <iostream>
#include <string>
using namespace std;

template <class T>
void Swap(T& a, T& b)
{
	T temp;
	temp = a;
	a = b;
	b = temp;
}

//���Ժ�ģ�干��
void Swap(int& a, double& b) 
{
	int temp;
	temp = a;
	a = b;
	b = temp;
}

void test1_temp_func()
{
	int x = 1, y = 2;
	double a = 1.3, b = 2.3;
	string s1 = "giao", s2 = "hello";
	cout << x << " " << y << endl;
	cout << a << " " << b << endl;
	cout << s1 << " " << s2 << endl;
	Swap(x, y);
	Swap(a, b);
	Swap(s1, s2);
	cout << x << " " << y << endl;
	cout << a << " " << b << endl;
	cout << s1 << " " << s2 << endl;
	cout << "--------------------------------------------------" << endl;
	//��ֵĲ���
	int xx = 1; double yy = 3.3;
	cout << xx << " " << yy << endl;
	Swap(xx, yy);
	cout << xx << " " << yy << endl;
	// Swap(yy, xx); // error,��ʹ����ʽ����ת��Ҳ�ᱻ���ԣ�������ģ���ʱ��
}



int main()
{
	test1_temp_func();
}
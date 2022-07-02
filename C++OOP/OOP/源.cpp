#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include "A.h"
using namespace std;

void MyPrintf(const char* p);
//const 不能通过这个来修改
void test1_const()
{
	int* ip;
	const int* cip;
	int i = 5;
	ip = &i;
	cip = &i;
	*ip = 10;
	//*cip = 15; //不能通过cip修改i的值

	const int ci = 3;
	//ip = &ci; //打破了对常量的保护，错误
	ip = (int*)&ci; //但强制类型转换可以
	cip = &ci; //没打破

	MyPrintf("giao");
}

//const的用途
//1. 希望在函数内不能修改指针指向的内容
void MyPrintf(const char* p)
{
	//strcpy((char *)p, "this"); //不可以修改，哪怕骗过编译器也会异常
	puts(p);
}
//2.const对象 与 const修饰函数——「不可修改的对象」
/* 1）「由来」：const对象指的是里面的data不能被修改，如何做到？
函数是要可以执行的,编译器不知道函数的具体实现，如何保证内部数据不被修改？const！*/
/* 2）const修饰的函数可以构成overload的关系，
因为参数表中一个是「A* this」 一个是「const A* this」*/
/* 3）不管怎样，const的变量一定要初始化的时候给一个值。
*/

void test2_const()
{
	const A ca(1);
	cout << ca.geti() << endl;
	//ca.seti()不能被调用，常量对象只能调用常量函数！
	A a(1);
	a.seti(5);
	cout << a.geti() << endl;
	//不是常量的对象，所有公有方法都可以调用
	ca.f();
	a.f();
	ca.print_arr();
}


void test1_reference()
{
	//引用的原则
	//1.一定是引用变量，不可以是「常量」和「表达式」。
	int i=1,j=2;
	const int ci=3;
	//int& x = ci; //错误！破坏了保护机制 const int &x = ci;是可以的
	//int& x = 3; //错误！不可以是表达式
	int& x = i;
	//2.引用从始至终只能引用一个变量,不能引用别人了
}

int main()
{
	test2_const();
	//test1_reference();
}
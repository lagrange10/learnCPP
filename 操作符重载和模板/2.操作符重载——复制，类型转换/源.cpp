#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

class Fi{
public:
    Fi(){ cout << "constructor Fi::Fi()" << endl; }
};
class Fee{
public:
    Fee(int) { cout << "constructor Fee(int)" << endl; }
    Fee(const Fi&){ cout << "constructor Fee(const Fi&)" << endl; }
    Fee& operator=(const Fee& fee) 
    {
        cout << "Fee::operator=" << endl;
        return *this;
    }
};

void test_assign(){
    Fee fee = 1;//Fee(int)
    
    Fi fi;
    Fee fum = fi;//Fee(Fi)
    
    fum	= fi;//????
}


//automatic operator= creation 自动给的赋值
// #d「memberwise」的意思是「按成员」 
// 这意味着如果成员是对象，那么会递归调用对象的构造函数;否则就直接拷贝过来
// #e 对于string类型的成员拷贝构造或者是默认的赋值运算符会去递归调用string的构造函数，
// 因而会自动分配空间; 而对于char *类型的成员,会直接拷贝过来，如果要使得赋值后两个实例
// 中的char *指向不同的地方，则需要按照下面的方法手动分配
class Cargo {
public:
    char* s;
    Cargo& operator=(const Cargo& that) {
        //手动分配空间
        if (this != &that)
        {
            delete s;
            s = new char[strlen(that.s)+1];
            strcpy(s, that.s);
            //s = that.s;
            cout << "inside Cargo::operator=()" << endl;
        }
        return *this;
    }
    Cargo() { s = new char[10]; }
};
class Truck {
public:
    char* s;
    Cargo b;
    Truck() { s = new char[10]; }
};

void test_memberwise_assignment() {
    Truck a, b;
    strcpy(b.b.s, "giao!");
    strcpy(b.s, "giao!");
    a = b;//prints:"inside Cargo::operator=()"
    printf("a的s地址是%p\n", a.b.s);
    printf("b的s地址是%p\n", b.b.s);

    printf("a的s地址是%p\n", a.s); //如果不写就是直接指向同一个地方
    printf("b的s地址是%p\n", b.s);
}

/* 开始测试「类型转换操作符」 operator type conversion */

//ambiguous type conversion Orange -> Apple; which type conversion will be use?

class Orange;//class declaration

class Apple {
public:
    int val_a;
    operator Orange() const;//Convert Apple to Orange
    Apple():val_a(0) {};
};

class Orange {
public:
    int val_o;
    Orange():val_o(0) {};
    explicit Orange(Apple);//Convert Apple to Orange
};

Orange::Orange(Apple a):val_o(a.val_a)
{
    cout << "Apple to Orange constructor" << endl;
}

Apple::operator Orange () const
{
    cout << "Apple to Orange operator type conversion" << endl;
    return Orange(*this);
}


void f(Orange) {}

void test_for_ambiguity()
{
    Apple a;
    f(a); //error if no explicit
    Orange o = (Orange) a; //强制类型转换调用了一个用一个Apple构造orange的构造函数
    o = Orange(a); //与直接调用构造函数相同
    
}

/* 测试「类型转换操作符」结束 */

int main()
{
    test_for_ambiguity();
}
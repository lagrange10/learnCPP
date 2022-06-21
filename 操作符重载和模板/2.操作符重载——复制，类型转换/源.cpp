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


//automatic operator= creation �Զ����ĸ�ֵ
// #d��memberwise������˼�ǡ�����Ա�� 
// ����ζ�������Ա�Ƕ�����ô��ݹ���ö���Ĺ��캯��;�����ֱ�ӿ�������
// #e ����string���͵ĳ�Ա�������������Ĭ�ϵĸ�ֵ�������ȥ�ݹ����string�Ĺ��캯����
// ������Զ�����ռ�; ������char *���͵ĳ�Ա,��ֱ�ӿ������������Ҫʹ�ø�ֵ������ʵ��
// �е�char *ָ��ͬ�ĵط�������Ҫ��������ķ����ֶ�����
class Cargo {
public:
    char* s;
    Cargo& operator=(const Cargo& that) {
        //�ֶ�����ռ�
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
    printf("a��s��ַ��%p\n", a.b.s);
    printf("b��s��ַ��%p\n", b.b.s);

    printf("a��s��ַ��%p\n", a.s); //�����д����ֱ��ָ��ͬһ���ط�
    printf("b��s��ַ��%p\n", b.s);
}

/* ��ʼ���ԡ�����ת���������� operator type conversion */

//ambiguous type conversion Orange -> Apple; which type conversion will be use?

class Orange;//class declaration

class Apple {
public:
    operator Orange() const;//Convert Apple to Orange
    Apple() {};
};

class Orange {
public:
    explicit Orange(Apple);//Convert Apple to Orange
};

Orange::Orange(Apple)
{

}

Apple::operator Orange () const
{
    cout << "Orange to Apple operator type conversion" << endl;
    return Orange(*this);
}


void f(Orange) {}

void test_for_ambiguity()
{
    Apple a;
    f(a); //error if no explicit
    Orange o = (Orange) a; //ǿ������ת����������������Լ����������ת��������
}

/* ���ԡ�����ת�������������� */

int main()
{
    test_for_ambiguity();
}
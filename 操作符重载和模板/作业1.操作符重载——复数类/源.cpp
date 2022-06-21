#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <cstdio>
using namespace std;

class Complex
{
private:
	double real, imag;
public:
	Complex(double real,double imag):real(real),imag(imag) {}
	Complex():real(0),imag(0) {}
	virtual ~Complex() {}
	Complex(const Complex& c) { real = c.real; imag = c.imag; }
	friend ostream& operator<<(ostream& o, const Complex &c);
	friend istream& operator>>(istream& o, Complex &c);
	friend const Complex operator+(const Complex& a, const Complex& b);
};

ostream& operator<<(ostream& o, const Complex &c)
{
	o << c.real << "+" << c.imag << "i";
	return o;
}

istream& operator>>(istream& i, Complex &c)
{
	//接收形如cin>>c; "3+4i"
	string s;
	i >> s;
	int pos = s.find('+', 0);
	string sTmp = s.substr(0, pos);
	c.real = atof(sTmp.c_str());
	sTmp = s.substr(pos+1, s.length()-1);
	c.imag = atof(sTmp.c_str());
	return i;
}

const Complex operator+(const Complex& a, const Complex& b)
{
	return Complex(a.real + b.real, a.imag + b.imag);
	//为啥 return Complex(a.real + b.real, a.imag + b.imag); 不行 
	//没有合适的copy constructor
}

int main()
{
	Complex c, d;
	cin >> c >> d;
	cout << c << endl << d << endl << c + d << endl;
}

/*
1+2i
3+4i
*/
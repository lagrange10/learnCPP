#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <cstring>
using namespace std;
class MyString {
	char* p;
public:
	MyString(const char* s) {
		if (s) {
			p = new char[strlen(s) + 1];
			strcpy(p, s);
		}
		else
			p = NULL;

	}
	~MyString() { if (p) delete[] p; }
	MyString(const MyString& s)
	{
		Copy(s);
	}
	void Copy(const MyString& s)
	{
		p = new char[strlen(s.p) + 1];
		strcpy(p, s.p);  //private是对类来说的。
	}
	friend ostream& operator<<(  ostream& o, const MyString &s )
	{
		o << s.p;
		return o;
	}
	MyString& operator=(const char *s)
	{
		delete[] p;
		p = new char[strlen(s) + 1];
		strcpy(p, s);
		return *this;
	}
	MyString& operator=(const MyString& s)
	{
		delete[] p;
		p = new char[strlen(s.p) + 1];
		strcpy(p, s.p);
		return *this;
	}
	// 在此处补充你的代码
};
int main()
{
	char w1[200], w2[100];
	while (cin >> w1 >> w2) {
		MyString s1(w1), s2 = s1;
		MyString s3(NULL);
		s3.Copy(w1);

		cout << s1 << "," << s2 << "," << s3 << endl;

		s2 = w2;
		s3 = s2;
		s1 = s3;
		cout << s1 << "," << s2 << "," << s3 << endl;

	}
}
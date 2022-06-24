#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>
using namespace std;

//构造函数对象就当函数用即可 只不过看起来多一个括号有点奇怪(构造函数0)
template <class T1, class T2>
struct Closer {
	// 在此处补充你的代码
private:
	T1 n;
	T2 dist;
public:
	Closer(T1 n, T2 dist):n(n),dist(dist){}
	bool operator()(T1 a, T1 b) //重载括号运算符别忘了加一个括号，声明成函数
	{
		if (dist(a, n) != dist(b, n))
		{
			return dist(a, n) < dist(b, n);
		}
		else
		{
			return a < b;
		}
	}
};

int Distance1(int n1, int n2) {
	return abs(n1 - n2);
}
int Distance2(const string& s1, const string& s2)
{
	return abs((int)s1.length() - (int)s2.length());
}
int a[10] = { 0,3,1,4,7,9,20,8,10,15 };
string b[6] = { "American","Jack","To","Peking","abcdefghijklmnop","123456789" };
int main()
{
	int n; string s;
	while (cin >> n >> s) {
		// 对数组a中的元素按和n的距离从小到大排序后输出。距离相同的，值小的排在前面。
		// Closer<int, int (*)(int, int)>(n, Distance1) 其实是用构造函数构造一个函数对象，用来传入sort
		sort(a, a + 10, Closer<int, int (*)(int, int)>(n, Distance1));
		for (int i = 0; i < 10; ++i)
			cout << a[i] << ",";
		cout << endl;
		sort(b, b + 6, Closer<string, int (*)(const string&, const string&)>(s, Distance2));
		for (int i = 0; i < 6; ++i)
			cout << b[i] << ",";
		cout << endl;
	}
	return 0;
}
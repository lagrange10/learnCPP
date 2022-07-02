#include <iostream> 
using namespace std;
class MyInt
{
	int nVal;
public:
	MyInt(int n) { nVal = n; }
	// 在此处补充你的代码
	MyInt& operator-(int i) 
	{
		//如果参数表写了int MyInt会咋样？
		//objInt - 2 - 1 - 3;会调用构造函数把2变成MyInt，如果写了到int的转换会混淆
		nVal -= i;
		return *this;
	}
	operator int () const
	{
		return nVal;
	}
};
int Inc(int n) {
	return n + 1;
}
int main() {
	int n;
	while (cin >> n) {
		MyInt objInt(n);
		objInt - 2 - 1 - 3;
		cout << Inc(objInt);
		cout << ",";
		objInt - 2 - 1;
		cout << Inc(objInt) << endl;
	}
	return 0;
}
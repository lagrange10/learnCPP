#include <iostream>
using namespace std;

//如何构造一个函数对象？
//自定义一个运算符()
template <class T>
struct GoodCopy {
	// 在此处补充你的代码
public:
	void operator()(T* src_begin, T* src_end, T* des_begin)
	{
		int elem_num = src_end - src_begin; //找到2个指针的间隔
		T* des_end = des_begin + elem_num; //指针可以直接＋间隔
		while (true)
		{
			*des_end-- = *src_end--; //*p--
			if (src_end == src_begin) //最后一次操作
			{
				*des_end = *src_end;
				break;
			}
		}
	}
};

int a[200];
int b[200];
string c[200];
string d[200];

template <class T>
void Print(T s, T e) {
	for (; s != e; ++s)
		cout << *s << ",";
	cout << endl;
}

int main()
{
	int t;
	cin >> t;
	GoodCopy<int> x = GoodCopy<int>();  //这其实是一个临时对象，可以调用()运算符
	while (t--) {
		int m;
		cin >> m;
		for (int i = 0; i < m; ++i)
			cin >> a[i];
		GoodCopy<int>()(a, a + m, b);     //这个可以视为将()重载
		Print(b, b + m);
		GoodCopy<int>()(a, a + m, a + m / 2);
		Print(a + m / 2, a + m / 2 + m);

		for (int i = 0; i < m; ++i)
			cin >> c[i];
		GoodCopy<string>()(c, c + m, d);
		Print(c, c + m);
		GoodCopy<string>()(c, c + m, c + m / 2);
		Print(c + m / 2, c + m / 2 + m);
	}
	return 0;
}
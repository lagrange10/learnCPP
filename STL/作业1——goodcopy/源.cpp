#include <iostream>
using namespace std;

//��ι���һ����������
//�Զ���һ�������()
template <class T>
struct GoodCopy {
	// �ڴ˴�������Ĵ���
public:
	void operator()(T* src_begin, T* src_end, T* des_begin)
	{
		int elem_num = src_end - src_begin; //�ҵ�2��ָ��ļ��
		T* des_end = des_begin + elem_num; //ָ�����ֱ�ӣ����
		while (true)
		{
			*des_end-- = *src_end--; //*p--
			if (src_end == src_begin) //���һ�β���
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
	GoodCopy<int> x = GoodCopy<int>();  //����ʵ��һ����ʱ���󣬿��Ե���()�����
	while (t--) {
		int m;
		cin >> m;
		for (int i = 0; i < m; ++i)
			cin >> a[i];
		GoodCopy<int>()(a, a + m, b);     //���������Ϊ��()����
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
#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;




int main()
{
	vector<int> v = { 3,5,7,9,11 };
	vector<int>::iterator j = find(v.begin(), v.end(), 9);
	int i = 0;
	for (; i < v.size(); i++)
	{
		cout << v[i] << " ";
		if (v[i] == 9) { v.erase(j); i--; }
	}
	/*cout << v.size() << endl;
	cout << v.empty() << endl;
	vector<int>::iterator ii = v.begin();
	ii = v.end();
	cout << (v.begin() == v.end()) << endl;
	int i = 1;*/

	return 0;
}


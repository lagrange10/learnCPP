#include <iostream>
#include <string>
using namespace std;

void test_string_basic()
{
	//init
	string s1("abc"), s2 = "123";
	string s3 = s2;
	cout << s1 << " " << s2 << " " << s3 << endl;

	//assign
	s2 = s1;
	s3.assign(s1, 1, 2);
	cout << s1 << " " << s2 << " " << s3 << endl;

	//traverse
	for (int i = 0; i < s1.length(); i++)
	{
		cout << s1.at(i) << " ";
	}
	cout << endl;

	s1[0] = s2[1] = 'g';
	cout << s1 << " " << s2 << " " << s3 << endl;
	//exception
	// s1.at(100); // exception
}

//常用的 连接append 删除 erase 子串substr 找字符find 替换replace
void test_string_common()
{
/* append & erase */
	cout << "--------------------------------------------------------" << endl;
	cout << "【append】" << endl;

	string s1("abc"), s2 = s1;
	string s3 = s1.append(s2);
	s1 = s2;
	cout << s1 << " " << s2 << " " << s3 << endl; //abc abc abcabc
	
	s3 = s1.append(s2,1,s2.length()); //从第1个字符开始，连接多少字符
	s1 = s2;
	cout << s1 << " " << s2 << " " << s3 << endl; //abc abc abcbc
	
	
	cout << "--------------------------------------------------------" << endl;
	cout << "【erase】" << endl;

	s3 = "hello world";
	s3.erase(5);
	cout << s3 << endl; //hello

/* end of append & erase */
	

/* 子串 substr ！！*/
	cout << "--------------------------------------------------------" << endl;
	cout << "【substr】" << endl;

	s3 = "hello world";
	s3 = s3.substr(1, 3); //下标为1 长度为3
	cout << s3 << endl; //ell

/* 查找find，rfind......*/
	cout << "--------------------------------------------------------" << endl;
	cout << "【find】" << endl;

	string s4 = "hello worlld";
	
	cout << s4.find("ll") << " " << s4.find("ll",2) << " " << s4.find("ll", 3) << " " << s4.rfind("ll") << endl;
	// 【ll】：2 2 9 9
	
	cout << string::npos << endl; 
	//找不到返回string::npos
	
	cout << s4.find_first_of("abcd") << " " << s4.find_last_of("o") << endl; //找abcd之中第一个出现的位置
	// 【d】:11 【o】:7
	
	cout << s4.find_first_not_of("abcd") << " " << s4.find_last_not_of("abcd") << endl;
	// 【not abcd】:0【not abcd】:10

/* 替换replace......*/
	cout << "--------------------------------------------------------" << endl;
	cout << "【replace】" << endl;

	s3 = "hello world";
	s3.replace(2, 3, "haha");
	cout << s3 << endl; //hehaha world

	s3 = "hello world";
	s3.replace(2, 3, "haha" , 1,2);
	cout << s3 << endl; //heah world

/* 插入insert......*/
	cout << "--------------------------------------------------------" << endl;
	cout << "【insert】" << endl;

	s3 = "hello world";
	s4 = "show insert";

	s3.insert(5, s4);
	cout << s3 << endl; //helloshow insert world

	s3 = "hello world";
	s3.insert(5, s4 ,5, 3);
	cout << s3 << endl; //helloins world
}


int main()
{
	// test_string_basic();
	test_string_common();
}
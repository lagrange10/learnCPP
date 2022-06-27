#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdio>
#include <cstdlib>
using namespace std;
//一些常用函数
class Factory
{
public:
	static void PrintVector(const vector<int>& l)
	{
		auto i = l.begin();
		for (i = l.begin(); i != l.end(); i++)
		{
			cout << *i << endl;
		}
	}
	static void PrintArray(const string* a, int size)
	{
		for (int i = 0; i < size; i++)
		{
			cout << a[i] << endl;
		}
	}
	static void PrintArray(const int* a, int size)
	{
		for (int i = 0; i < size; i++)
		{
			cout << a[i] << endl;
		}
	}
};

class Warrior
{
#define DRAGON 0
#define NINJA 1
#define ICEMAN 2
#define LION 3
#define WOLF 4
private:
	/* 战士属性 */
	int id; //游戏中的编号 ID是类型编号，数组下标
	
	int curLife; //当前生命

	static const int warriorTypeCnt = 5;
public:
	/* 一些全局可用的信息，战士列表ID-名字-花费 */
	static vector<int> warriorCost;  //战士花费
	static vector<string> warriorName;  //战士名字

	// 构造函数，id
	Warrior() :id(0) {}
	Warrior(int id):id(id) {}

	// 获得战士的编号（id）
	int Get_id() { return id; }

	//可以将战士名字转换为类型编号ID,如果不存在，返回-1;
	static int NameToID(string name)
	{
		auto i = warriorName.begin();
		int ID = 0,ret = -1;
		for (; i != warriorName.end(); i++)
		{
			if (*i != name)
			{
				ID++;
			}
			else
			{
				ret = ID;
			}
		}
		return ret;
	}
};

vector<int> Warrior::warriorCost;     //战士花费
vector<string> Warrior::warriorName;   //战士名字

/* ---------------------------武器类------------------------- */
class Weapon
{
public:
	/* 一些全局可用的信息，武器列表ID-名字 */
	static vector<string> weaponName;  //武器名字

};

vector<string> Weapon::weaponName;   //武器名字

/* ---------------------------武器类结束------------------------- */

/* ---------------------------各类战士------------------------- */
//龙
class Dragon :public Warrior
{
public:
	static int lifeCost; // 消耗的生命元
	static int ID; //该战士的类型编号ID
	static string tag; //这个战士的名字
private:
	int weaponID; // 拥有的武器编号，自己制造时编号为n，武器为n%3
	float morale; // 士气，Dragon独有，值为它降生后「司令部剩余生命元的数量」除以「造dragon所需的生命元数量」
public:
	//默认构造函数，不使用
	Dragon():weaponID(0), morale(0){ }
	//龙构造函数：初始化武器和士气
	Dragon(int weaponID, float morale, int id):weaponID(weaponID), morale(morale), Warrior(id){}
	//获得武器编号
	int GetWeaponID() { return weaponID; }
	//获得武器名字
	string GetWeaponName(int ID) { return Weapon::weaponName[ID]; }
	//获得士气
	float GetMorale() { return morale; }
};

//忍者
class Ninja :public Warrior
{
public:
	static int lifeCost; // 消耗的生命元
	static int ID; //该战士的类型编号ID
	static string tag; //这个战士的名字
private:
	int weaponID1; // 拥有的武器编号1，自己制造时编号为n，武器为n%3
	int weaponID2; // 拥有的武器编号2，自己制造时编号为n，武器为（n+1）%3
public:
	//默认构造函数，不使用
	Ninja():weaponID1(0), weaponID2(0) { }
	//龙构造函数：初始化武器和士气
	Ninja(int weaponID1, int weaponID2) :weaponID1(weaponID1), weaponID2(weaponID2){}
	//获得武器编号1
	int GetWeaponID1() { return weaponID1; }
	//获得武器编号2
	int GetWeaponID2() { return weaponID2; }
	//获得武器名字
	string GetWeaponName(int ID) { return Weapon::weaponName[ID]; }
};
//冰人
class Iceman :public Warrior
{
public:
	static int lifeCost; // 消耗的生命元
	static int ID; //该战士的类型编号ID
	static string tag; //这个战士的名字
private:
	int weaponID; // 拥有的武器编号，自己制造时编号为n，武器为n%3
public:
	//默认构造函数，不使用
	Iceman():weaponID(0) { }
	//龙构造函数：初始化武器和士气
	Iceman(int weaponID) :weaponID(weaponID) {}
	//获得武器编号
	int GetWeaponID() { return weaponID; }
	//获得武器名字
	string GetWeaponName(int ID) { return Weapon::weaponName[ID]; }
};

//狮子
class Lion :public Warrior
{
public:
	static int lifeCost; // 消耗的生命元
	static int ID; //该战士的类型编号ID
	static string tag; //这个战士的名字
private:
	int loyalty; //忠诚度，Lion独有，值等于「它降生后其司令部剩余生命元的数目」。
public:
	//默认构造函数，不使用
	Lion():loyalty(0) { }
	//龙构造函数：初始化武器和士气
	Lion(int loyalty) :loyalty(loyalty) {}
	int GetLoyalty() { return loyalty; }
};

//狼
class Wolf :public Warrior
{
public:
	static int lifeCost; // 消耗的生命元
	static int ID; //该战士的类型编号ID
	static string tag; //这个战士的名字
public:
	//默认构造函数，wolf没有特点
	Wolf() {}
};

int Dragon::lifeCost;
int Ninja::lifeCost;
int Iceman::lifeCost;
int Lion::lifeCost;
int Wolf::lifeCost;
int Dragon::ID;
int Ninja::ID;
int Iceman::ID;
int Lion::ID;
int Wolf::ID;
string Dragon::tag = "dragon";
string Ninja::tag = "ninja";
string Iceman::tag = "iceman";
string Lion::tag = "lion";
string Wolf::tag = "wolf";

/* ---------------------------各类战士结束------------------------- */

//只有一份时间
class Timer
{
private:
	static int now; // 当前时间
public:
	//获得当前时间
	static int GetTime() { return now; }
	//将时间初始化为0
	static void InitTime() { now = 0; }
	//将时间+1
	static void UpdateTime() { now++; }
};

int Timer::now = 0; // 当前时间

//司令部
class Headquarters
{
private:

	
	static const int warriorTypeCnt = 5; //兵种个数
	static const int circuCnt = 5; //循环次数
	string order[circuCnt]; //顺序
	int turn; //轮次

	string curWarrior; //当前时间要出的兵种
	int curWarriorCnt[warriorTypeCnt]; //当前战士数量
	string colorName; //红色方，蓝色方
	int curLifeElem; //当前司令部生命
	bool isEnd;
public:
	vector<int> warriorCostByOrder; //按顺序的战士花销
	static int initLife; //初始生命
	bool hasLife; //是否有生命元可以出兵

	//指挥部构造函数
	Headquarters(string name) :colorName(name), hasLife(true)
		, curLifeElem(initLife), turn(0), isEnd(false)
	{
		//初始化order数组
		if (name == "red")
		{
			order[0] = "iceman";
			order[1] = "lion";
			order[2] = "wolf";
			order[3] = "ninja";
			order[4] = "dragon";
		}
		else
		{
			order[0] = "lion";
			order[1] = "dragon";
			order[2] = "ninja";
			order[3] = "iceman";
			order[4] = "wolf";
		}
		memset(curWarriorCnt, 0, sizeof(curWarriorCnt));

		//初始化warriorCostByOrder
		for (int i = 0; i < warriorTypeCnt; i++)
		{
			int ID = Warrior::NameToID(order[i]);
			warriorCostByOrder.emplace_back(Warrior::warriorCost[ID]);
		}
	}

	virtual ~Headquarters() {}

	int GetLifeElem() { return curLifeElem; }

	void SetLifeElem(int x) { curLifeElem = x; }

	//指挥部随时间更新
	void Update()
	{
		if (isEnd) return;
		int time = Timer::GetTime();
		int id = time + 1;
		//判断生命值是否足够，选择第一个能出的兵种
		int cnt = warriorTypeCnt; //计数器，尝试出兵5次以后就跳出循环
		while (curLifeElem < warriorCostByOrder[turn % warriorTypeCnt])
		{
			turn++; cnt--;
			if (cnt == 0)
			{
				hasLife = false;
				break;
			}
		}

		//选择能出的兵种
		curWarrior = order[turn % circuCnt];
		//对应的兵种++
		int curID = Warrior::NameToID(curWarrior);
		curWarriorCnt[curID]++;
	
		//生命之源--
		int strength = Warrior::warriorCost[curID]; //消耗的生命源就是战士的生命值
		curLifeElem -= strength;

		/* 实例化该兵种 */
		Dragon d;
		Ninja n;
		Iceman i;
		Lion l;
		Wolf w;
		switch (curID)
		{
		case DRAGON:
			d = Dragon(id % 3, curLifeElem / ((float)Dragon::lifeCost), id);
		case NINJA:
			n = Ninja(id % 3, (id + 1) % 3);
		case ICEMAN:
			i = Iceman(id % 3);
		case LION:
			l = Lion(curLifeElem);
		case WOLF:
			w = Wolf();
		default:
			break;
		}
		//打印出兵信息
		if (time < 10)
		{
			printf("00");
		}
		else if (time < 100)
		{
			printf("0");
		}
		if (hasLife)
		{
			printf("%d %s %s %d born with strength %d,%d %s in %s headquarter\n",
				time, colorName.c_str(),
				curWarrior.c_str(), 
				time + 1,
				strength, curWarriorCnt[curID],
				curWarrior.c_str(), colorName.c_str()
			);
			switch (curID)
			{
			case DRAGON:
				printf("It has a %s,and it's morale is %.2f\n",
					Weapon::weaponName[d.GetWeaponID()].c_str(),
					d.GetMorale()
				);
				break;
			case NINJA:
				printf("It has a %s and %s\n",
					Weapon::weaponName[n.GetWeaponID1()].c_str(),
					Weapon::weaponName[n.GetWeaponID2()].c_str()
				);
				break;
			case ICEMAN:
				printf("It has a %s\n",
					Weapon::weaponName[i.GetWeaponID()].c_str()
				);
				break;
			case LION:
				printf("it's loyalty is %d\n",
					l.GetLoyalty()
				);
				break;
			default:
				break;
			}
		}
		else
		{
			cout << time;
			cout << " " + colorName + " headquarter stops making warriors" << endl;
			isEnd = true;
		}
		turn++; //轮到下一个兵种
	}
};

int Headquarters::initLife;

class Input
{
public:
	//项目初始化，给一些静态变量赋值
	static void InitProject()
	{
		Warrior::warriorName.emplace_back("dragon");
		Warrior::warriorName.emplace_back("ninja");
		Warrior::warriorName.emplace_back("iceman");
		Warrior::warriorName.emplace_back("lion");
		Warrior::warriorName.emplace_back("wolf");
		Weapon::weaponName.emplace_back("sword");
		Weapon::weaponName.emplace_back("bomb");
		Weapon::weaponName.emplace_back("arrow");
	}

	//输入数据
	static void InputData()
	{
		cin >> Headquarters::initLife;
		cin >> Dragon::lifeCost >> Ninja::lifeCost
			>> Iceman::lifeCost >> Lion::lifeCost >> Wolf::lifeCost;
		
		/* 输入武士编号 */
		Dragon::ID = 0;
		Ninja::ID = 1;
		Iceman::ID = 2;
		Lion::ID = 3;
		Wolf::ID = 4;

		/* 读入武士花费 */
		Warrior::warriorCost.clear(); //清理上次的数据
		Warrior::warriorCost.emplace_back(Dragon::lifeCost);
		Warrior::warriorCost.emplace_back(Ninja::lifeCost);
		Warrior::warriorCost.emplace_back(Iceman::lifeCost);
		Warrior::warriorCost.emplace_back(Lion::lifeCost);
		Warrior::warriorCost.emplace_back(Wolf::lifeCost);
		//PrintVector(Warrior::warriorCost);
	}
};

int main()
{
	Input::InitProject();
	int cnt, n = 0; // cnt: 数据组数 n: 该组数据的编号
	cin >> cnt;
	while (cnt--)
	{
		Timer::InitTime();
		n++;
		Input::InputData(); //输入数据
		Headquarters red("red"), blue("blue");
		cout << "Case:" << n << endl;
		//cout events
		while (red.hasLife || blue.hasLife)
		{
			red.Update();
			blue.Update();
			Timer::UpdateTime(); //更新时间
		}
	}


}
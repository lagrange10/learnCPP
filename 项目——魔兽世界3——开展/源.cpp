#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdio>
#include <cstdlib>
using namespace std;

//整个项目的基本参数，一些常用函数
class Factory
{
public:
	static int cityNum; //城市数量
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

int Factory::cityNum; //城市数量

class Warrior
{
#define DRAGON 0
#define NINJA 1
#define ICEMAN 2
#define LION 3
#define WOLF 4
protected:
	/* 战士属性 */
	int id; //游戏中的编号 ID是类型编号，数组下标
	int curLife; //当前生命
	float attack; //攻击力

	/* 战士武器数量 */
	vector<int> weapon_num;
	int arrow_no_use; //没用过的arrow，保持与arrow_num-1一致
	
	
	static const int warriorTypeCnt = 5; //战士种类数
public:
	/* 一些全局可用的信息，战士列表ID-名字-花费 */
	static vector<int> warriorCost;  //战士花费
	static vector<string> warriorName;  //战士名字


	// 构造函数，id
	Warrior(int id) :id(id) 
	{ 
		for (int i = 0; i < 3; i++) weapon_num.emplace_back(0);
	}

	Warrior(int id,int cost) :id(id),curLife(cost)
	{
		for (int i = 0; i < 3; i++) weapon_num.emplace_back(0);
	}

	// 获得战士的武器Vector3
	vector<int>& GetWeapon(vector<int>& v)
	{
		v = weapon_num;
		return v;
	}

	// 获得战士的编号（id）
	int GetID() { return id; }

	// 获得战士的当前生命
	int GetCurLife() { return curLife; }

	//可以将战士名字转换为类型编号ID,如果不存在，返回-1;
	static int NameToID(string name)
	{
		auto i = warriorName.begin();
		int ID = 0, ret = -1;
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
#define WEAPON_NUM 3
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
	static int attack; // 该战士的攻击力
	static string tag; //这个战士的名字
private:
	float morale; // 士气，Dragon独有，值为它降生后「司令部剩余生命元的数量」除以「造dragon所需的生命元数量」
public:
	//默认构造函数，不使用
	Dragon(int id): morale(0), Warrior(id,lifeCost){ }
	//龙构造函数：初始化武器和士气
	Dragon(float morale, int id): morale(morale), Warrior(id,lifeCost) 
	{
		weapon_num[id % 3]++;
		
	}
	//获得士气
	float GetMorale() { return morale; }
};

//忍者
class Ninja :public Warrior
{
public:
	static int lifeCost; // 消耗的生命元
	static int ID; //该战士的类型编号ID
	static int attack; // 该战士的攻击力
	static string tag; //这个战士的名字
private:
public:
	Ninja(int id):Warrior(id, lifeCost)
	{
		weapon_num[id % 3]++;
		weapon_num[(id + 1) % 3]++;
	}
};
//冰人
class Iceman :public Warrior
{
public:
	static int lifeCost; // 消耗的生命元
	static int ID; //该战士的类型编号ID
	static int attack; // 该战士的攻击力
	static string tag; //这个战士的名字
public:
	//龙构造函数：初始化武器和士气
	Iceman(int id) :Warrior(id, lifeCost)
	{
		weapon_num[id % 3]++;
	}
};

//狮子
class Lion :public Warrior
{
public:
	static int lifeCost; // 消耗的生命元
	static int ID; //该战士的类型编号ID
	static int attack; // 该战士的攻击力
	static string tag; //这个战士的名字static
	static int loyaltyLoss; //每走一步损失的忠诚度
private:
	int loyalty; //忠诚度，Lion独有，值等于「它降生后其司令部剩余生命元的数目」。
public:
	//默认构造函数，不使用
	Lion(int id) :loyalty(0), Warrior(id, lifeCost) { }
	//龙构造函数：初始化武器和士气
	Lion(int loyalty,int id) :loyalty(loyalty), Warrior(id, lifeCost)
	{
		weapon_num[id % 3]++;
	}
	int GetLoyalty() { return loyalty; }
};

int Lion::loyaltyLoss;

//狼
class Wolf :public Warrior
{
public:
	static int lifeCost; // 消耗的生命元
	static int ID; //该战士的类型编号ID
	static int attack; // 该战士的攻击力
	static string tag; //这个战士的名字
public:
	//默认构造函数，wolf没有特点
	Wolf(int id): Warrior(id, lifeCost) {}
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

int Dragon::attack;
int Ninja::attack;
int Iceman::attack;
int Lion::attack;
int Wolf::attack;

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
	static int totalGameTime; //总共进行几分钟游戏
	//获得当前时间
	static int GetTime() { return now; }
	//将时间初始化为0
	static void InitTime() { now = 0; }
	//将时间+1
	static void UpdateTime() { now++; }
};

int Timer::now = 0; // 当前时间
int Timer::totalGameTime; //总共进行几分钟游戏
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
	string name; //红色方，蓝色方
	int curLife; //当前司令部生命
	bool end;
public:
	vector<int> warriorCostByOrder; //按顺序的战士花销
	static int initLife; //初始生命
	bool hasLife; //是否有生命元可以出兵

	//指挥部构造函数
	Headquarters(string name) :name(name), hasLife(true)
		, curLife(initLife), turn(0), end(false)
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

	int getLife() { return curLife; }

	void setLife(int x) { curLife = x; }

	//指挥部随时间更新
	void Update()
	{
		if (end) return;
		int time = Timer::GetTime();
		int id = time + 1;
		//判断生命值是否足够，选择第一个能出的兵种
		int cnt = warriorTypeCnt; //计数器，尝试出兵5次以后就跳出循环
		while (curLife < warriorCostByOrder[turn % warriorTypeCnt])
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
		curLife -= strength;

		/* 实例化该兵种 */
		Warrior* war_list[warriorTypeCnt];
		switch (curID)
		{
		case DRAGON:
			war_list[DRAGON] = new Dragon(curLife / ((float)Dragon::lifeCost), id);
			break;
		case NINJA:
			war_list[NINJA] = new Ninja(id);
			break;
		case ICEMAN:
			war_list[ICEMAN] = new Iceman(id);
			break;
		case LION:
			war_list[LION] = new Lion(curLife, id); //忠诚度就是当前司令部的生命curLife
			break;
		case WOLF:
			war_list[WOLF] = new Wolf(id);
			break;
		default:
			break;
		}

		/* 获得武器数量 */
		vector<int> weapon_num;
		war_list[curID]->GetWeapon(weapon_num);
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
				time, name.c_str(),
				curWarrior.c_str(),
				id,
				strength, curWarriorCnt[curID],
				curWarrior.c_str(), name.c_str()
			);
			printf("%s %s %d has %d sword %d bomb %d arrow and %d elements\n",
				name.c_str(),
				curWarrior.c_str(),
				id, 
				weapon_num[0],
				weapon_num[1],
				weapon_num[2],
				war_list[curID]->GetCurLife()
			);
		
		}
		else
		{
			cout << time;
			cout << " " + name + " headquarter stops making warriors" << endl;
			end = true;
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
		cin >> Headquarters::initLife >> Factory::cityNum >> 
			Lion::loyaltyLoss >> Timer::totalGameTime;
		cin >> Dragon::lifeCost >> Ninja::lifeCost
			>> Iceman::lifeCost >> Lion::lifeCost >> Wolf::lifeCost;
		cin >> Dragon::attack >> Ninja::attack
			>> Iceman::attack >> Lion::attack >> Wolf::attack;
		
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
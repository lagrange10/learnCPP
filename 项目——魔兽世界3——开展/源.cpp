#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#define RED 0
#define BLUE 1
#define SWORD 0
#define BOMB 1
#define ARROW 2
using namespace std;

//整个项目的基本参数，一些常用函数
class Warrior;
class City
{
private:
	int index;
	int turn;
	Warrior* r_w; //红方战士
	Warrior* b_w; //蓝方战士
public:
	City() :r_w(NULL), b_w(NULL), turn(RED), index(0) {}
	void setIndex(int i){ index = i; }
	void setWarrior(Warrior* r, Warrior* b){ r_w = r; b_w = b; }
	void battle();
};

/* 只有一份时间 */
class Timer
{
private:
	static int hour; // 当前小时
	static int min; // 当前分钟
public:
	static int totalGameTime; //总共进行几分钟游戏
	//获得当前时间
	static int GetTime() { return hour; }
	//将时间初始化为0
	static void InitTime() { hour = 0; min = 0; }
	//将小时+1
	static void UpdateHour() { hour++; min = 0; }
	//更新分钟，给分钟+min
	static void UpdateMin(int minute) { min += minute; }
	//打印时间
	static void PrintTime();
};

int Timer::hour = 0; // 当前时间
int Timer::min = 0; // 当前时间
int Timer::totalGameTime; //总共进行几分钟游戏

class Headquarters
{
private:


	static const int warriorTypeCnt = 5; //兵种个数
	static const int circuCnt = 5; //循环次数
	string order[circuCnt]; //顺序
	int turn; //轮次

	string curWarriorName; //当前时间要出的兵种
	int curWarriorCnt[warriorTypeCnt]; //当前战士数量

	int color;  //红=0，蓝=1
	string colorName; //红色方，蓝色方

	int curLifeElem; //当前司令部生命元
	bool isEnd; //司令部是否结束出兵
public:
	vector<int> warriorCostByOrder; //按顺序的战士花费
	static int initLife; //初始生命
	bool hasLife; //是否有生命元可以出兵

public:
	//指挥部构造函数
	Headquarters(int color);

	virtual ~Headquarters() {}

	//获得当前生命元
	int GetLifeElem() { return curLifeElem; }

	//设置当前的生命元
	void SetLifeElem(int x) { curLifeElem = x; }

	/* 一个小时内发生的事件 */
	//武士降生 0min
	void WarriorsBirth();

	//司令部报告状态 50min
	void HeadquartersStatus();

	//指挥部随时间更新
	Warrior* SelectWarrior();

	void printEvents(Warrior* curWarrior);
};

int Headquarters::initLife;
/* 司令部类结束 */

class Warrior
{
#define DRAGON 0
#define NINJA 1
#define ICEMAN 2
#define LION 3
#define WOLF 4
protected:
	/* 战士属性 */
	int id; //游戏中的编号
	int ID; //战士类型 0-4
	int curLife; //当前生命
	float attack; //攻击力
	bool isDead; //是否死亡

	/* 阵营 */
	int color;
	string colorName;
	Headquarters* team; //阵营指针

	/* 战士武器数量 */
	vector<int> weapon_num;


	static const int warriorTypeCnt = 5; //战士种类数
public:
	/* 一些全局可用的信息，战士列表ID-名字-花费 */
	static vector<int> warriorCost;  //战士花费
	static vector<string> warriorName;  //战士名字


	// 构造函数，id
	Warrior(int id = 0, int cost = 0, int ID = 0, int color = 0, Headquarters* team = NULL);

	// 获得战士的武器Vector3
	int GetWeaponNum(int type){ return weapon_num[type]; }

	// 获得战士的编号（id）
	int Get_id() { return id; }

	// 获得战士的类型（ID）
	int Get_ID() { return ID; }

	// 获得战士的名称
	string GetName() { return warriorName[ID]; }

	// 获得战士的当前生命
	int GetCurLife() { return curLife; }

	// 获得狮子的忠诚度
	virtual int GetLoyalty(){ return -1; }

	/* 设置 */
	//死亡
	void Die()
	{
		isDead = true;
		/* 从team的战士列表中移除这个战士 */
	}

	//受伤
	void Hurt(unsigned int val);

	//武士报告状态 55min
	void WarriorsStatus();

	//可以将战士名字转换为类型编号ID,如果不存在，返回-1;
	static int NameToID(string name);
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
	Dragon(int id, int color) : morale(0), Warrior(id, lifeCost, DRAGON, color) { }
	//龙构造函数：初始化武器和士气
	Dragon(float morale, int id, int color) : morale(morale), Warrior(id, lifeCost, DRAGON, color)
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
	Ninja(int id, int color) :Warrior(id, lifeCost, NINJA, color)
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
	Iceman(int id, int color) :Warrior(id, lifeCost, ICEMAN, color)
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
	Lion(int id, int color) :loyalty(0), Warrior(id, lifeCost, LION, color) { }
	//龙构造函数：初始化武器和士气
	Lion(int loyalty, int id, int color) :loyalty(loyalty), Warrior(id, lifeCost, LION, color)
	{
		weapon_num[id % 3]++;
	}
	virtual int GetLoyalty() { return loyalty; }

	//忠诚度损失
	void LoyaltyLoss(unsigned int val)
	{
		loyalty -= val;
	}

	//逃跑，并报告
	void run()
	{
		if (loyalty < 0)
		{
			Die();
			Timer::PrintTime();
			printf("%s lion %d ran away",
				colorName.c_str(),
				id
			);
		}
	}
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
	Wolf(int id, int color) : Warrior(id, lifeCost, WOLF, color) {
	}
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


class Factory
{
#define MAXCITYNUM 22
public:
	static int cityNum; //城市数量
	static City city_list[MAXCITYNUM]; // 城市数组
	Headquarters* head_red, * head_blue; //双方指挥部
public:
	Factory();
	
	//项目开始
	void Start(int& n)
	{
		Timer::InitTime();
		n++;
		InputData(); //输入数据
		head_red = new Headquarters(RED);
		head_blue = new Headquarters(BLUE);
		cout << "Case:" << n << endl;
		//cout events
		while (head_red->hasLife || head_blue->hasLife)
		{
			Update();
			Timer::UpdateHour(); //更新时间
		}
	}

	//一个小时内的事情与打印日志
	void Update()
	{
		head_red->WarriorsBirth();
		head_blue->WarriorsBirth();
		Timer::UpdateMin(5);
		/* lion run */
		Timer::UpdateMin(5);
		/* forward */
		Timer::UpdateMin(25);
		/* wolf */
		Timer::UpdateMin(5);
		/* battle */
		Timer::UpdateMin(10);
		head_red->HeadquartersStatus();
		head_blue->HeadquartersStatus();
		
		Timer::UpdateMin(5);
		Warriors_report();
	}

	void Warriors_report()
	{
		/* warriors report*/
	}

	//初始化项目
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


void City::battle()
{
	turn = (index % 2 == 1) ? RED : BLUE; //奇数城市，红先攻击
		
	/* 战斗过程 */
	if (RED == turn)
	{

	}
	else
	{

	}
		
}


City Factory::city_list[MAXCITYNUM]; //城市数组


Headquarters::Headquarters(int color) :color(color), hasLife(true)
	, curLifeElem(initLife), turn(0), isEnd(false)
{

	//初始化order数组
	if (color == RED)
	{
		colorName = "red";
		order[0] = "iceman";
		order[1] = "lion";
		order[2] = "wolf";
		order[3] = "ninja";
		order[4] = "dragon";
	}
	else
	{
		colorName = "blue";
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

//武士降生 0min
void Headquarters::WarriorsBirth()
{
	Warrior* w = SelectWarrior();
	if (NULL == w) return;
	Timer::PrintTime();
	cout << colorName + " " << w->GetName() + " " << w->Get_id() << " born" << endl;
	if (w->Get_ID() == LION)
	{
		cout << "Its loyalty is " << w->GetLoyalty() << endl;
	}
}

//司令部报告状态 50min
void Headquarters::HeadquartersStatus()
{
	Timer::PrintTime();
	printf("%d elements in %s headquarter\n",
		curLifeElem,
		colorName.c_str()
	);
}

//挑选一个战士,失败返回NULL
Warrior* Headquarters::SelectWarrior()
{
	if (isEnd) return NULL;
	int time = Timer::GetTime();
	int id = time + 1;
	/* 判断生命值是否足够,一旦不够就停止出兵 */
	if (curLifeElem < warriorCostByOrder[turn % warriorTypeCnt])
	{
		hasLife = false;
		cout << colorName + " headquarter stops making warriors" << endl;
		isEnd = true;
		return NULL;
	}

	//选择能出的兵种
	curWarriorName = order[turn % circuCnt];
	//对应的兵种++
	int curID = Warrior::NameToID(curWarriorName);
	curWarriorCnt[curID]++;

	//生命之源--
	int strength = Warrior::warriorCost[curID]; //消耗的生命源就是战士的生命值
	curLifeElem -= strength;

	/* 实例化该兵种 */
	Warrior* curWarrior = new Warrior();
	switch (curID)
	{
	case DRAGON:
		curWarrior = new Dragon(curLifeElem / ((float)Dragon::lifeCost), id, color);
		break;
	case NINJA:
		curWarrior = new Ninja(id, color);
		break;
	case ICEMAN:
		curWarrior = new Iceman(id, color);
		break;
	case LION:
		curWarrior = new Lion(curLifeElem, id, color); //忠诚度就是当前司令部的生命curLife
		break;
	case WOLF:
		curWarrior = new Wolf(id, color);
		break;
	default:
		break;
	}
	
	turn++;
	return curWarrior;
}

void Headquarters::printEvents(Warrior *curWarrior)
{
	if (hasLife)
	{
		WarriorsBirth();
		/*printf("%s %s %d born with strength %d,%d %s in %s headquarter\n",
			colorName.c_str(),
			curWarrior->GetName().c_str(),
			id,
			strength, curWarriorCnt[curID],
			curWarrior->GetName().c_str(), colorName.c_str()
		);*/
		HeadquartersStatus();
		curWarrior->WarriorsStatus();
	}
	else if(!isEnd)
	{
		cout << colorName + " headquarter stops making warriors" << endl;
		isEnd = true;
	}
	turn++; //轮到下一个兵种
}


int main()
{
	Factory::InitProject();
	int cnt, n = 0; // cnt: 数据组数 n: 该组数据的编号
	cin >> cnt;
	while (cnt--)
	{
		Factory f;
		f.Start(n);
	}
}


/* -----------------------武士方法的实现----------------------- */
// 构造函数，id
inline Warrior::Warrior(int id, int cost, int ID, int color, Headquarters* team) :
	id(id), curLife(cost), ID(ID), color(color), weapon_num(vector<int>(3)),
	isDead(false), team(team)
{
	if (RED == color)
	{
		colorName = "red";
	}
	else
	{
		colorName = "blue";
	}
}

//受伤

inline void Warrior::Hurt(unsigned int val)
{
	curLife -= val;
	if (curLife < 0)
	{
		curLife = 0;
		Die();
	}
}

//武士报告状态 55min

inline void Warrior::WarriorsStatus()
{
	Timer::PrintTime();
	printf("%s %s %d has %d sword %d bomb %d arrow and %d elements\n",
		colorName.c_str(),
		GetName().c_str(),
		Get_id(),
		GetWeaponNum(SWORD),
		GetWeaponNum(BOMB),
		GetWeaponNum(ARROW),
		GetCurLife()
	);
}

//可以将战士名字转换为类型编号ID,如果不存在，返回-1;

inline int Warrior::NameToID(string name)
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
/* -----------------------武士方法的实现结束----------------------- */

//打印时间
inline void Timer::PrintTime()
{
	if (hour < 10)
	{
		cout << "00";
	}
	else if (hour < 100)
	{
		cout << "0";
	}
	cout << hour << ":";
	if (min < 10)
	{
		cout << "0";
	}
	cout << min << " ";
}

inline Factory::Factory() :head_red(NULL), head_blue(NULL)
{
	/* 城市初始化索引 */
	for (int i = 0; i <= cityNum + 1; i++)
	{
		city_list[i].setIndex(i); //下标为0红方基地，下表为cityNum+1为蓝方基地
	}
}

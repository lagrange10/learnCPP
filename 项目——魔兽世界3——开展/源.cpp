#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#define RED 0
#define BLUE 1
#define SWORD 0
#define BOMB 1
#define ARROW 2
using namespace std;

//整个项目的基本参数，一些常用函数
class Warrior;
class Factory;
class Weapon;
class Wolf;
class City
{
private:
	int index;
	int turn;
	Warrior* r_w; //红方战士
	Warrior* b_w; //蓝方战士
public:
	City() :r_w(NULL), b_w(NULL), turn(RED), index(0) {}

	//设置索引
	void SetIndex(int i){ index = i; }

	//设置红方战士
	void SetRedWarrior(Warrior* r){ r_w = r; }

	//设置蓝方战士
	void SetBlueWarrior(Warrior* b) { b_w = b; }

	//获得城市索引
	int Get_id() { return index; }

	//检查战斗结果,结束返回0,没结束返回-1
	int CheckResult(Warrior* r, Warrior* b);

	//在城市里战斗
	void Battle();
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
	vector<Warrior*> curWarriorList; //当前战士列表

	int color;  //红=0，蓝=1
	string colorName; //红色方，蓝色方

	int curLifeElem; //当前司令部生命元
	bool canProduce; //司令部是否结束出兵
	bool isOccupied; //是否被占领
public:
	vector<int> warriorCostByOrder; //按顺序的战士花费
	static int initLife; //初始生命
	bool hasLife; //是否有生命元可以出兵
	Factory* pf; //这个工程
public:
	//指挥部构造函数
	Headquarters(int color,Factory* pf);

	virtual ~Headquarters() {}

	//获得当前的工程factory
	Factory* GetFactory() { return pf; }

	//获得当前生命元
	int GetLifeElem() { return curLifeElem; }

	//设置当前的生命元
	void SetLifeElem(int x) { curLifeElem = x; }

	//被占领
	void beOccupied();

	/* 一个小时内发生的事件 */
	//武士降生 0min
	int WarriorsBirth();

	//武士前进 10mmin
	void WarriorsMarch();

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
	float warrior_ATK; //攻击力
	bool isDead; //是否死亡

	/* 阵营 */
	int color;
	string colorName;
	Headquarters* team; //阵营指针

	/* 战士的武器 */
	vector<int> weapon_num;
	vector<Weapon*> weaponList;

	int city; //在哪座城市

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

	// 是否死亡
	bool IsDead() { return isDead; }

	/* 设置 */
	//死亡
	void Die()
	{
		isDead = true;
		/* 从team的战士列表中移除这个战士 */
	}

	//攻击
	void Attack(Warrior* enemy);
	
	//抢夺武器
	void Stole(Warrior* enemy);

	//受伤
	void Hurt(unsigned int val);

	//前进
	void March();

	//挑选武器
	Weapon* SelectWeapon();

	//没武器了
	bool IsWeaponEmpty() { return weaponList.empty(); }

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
#define INFINITY -1
public:
	/* 一些全局可用的信息，武器列表ID-名字 */
	static vector<string> weaponName;  //武器名字
private:
	int ATK_damage;  //攻击力
	int use_cnt; //使用次数
	int type; //武器类型
public:
	Weapon(int ATK, int type);
	bool operator<(Weapon* that);
	bool operator==(Weapon* that);
	int GetATK() { return ATK_damage; }
	int GetUseTime() { return use_cnt; }
	int GetType() { return type; }

	void UseTimeDecline() { use_cnt--; }
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
	Dragon(float morale, int id, int color, Headquarters *ph) : morale(morale), Warrior(id, lifeCost, DRAGON, color, ph)
	{
		weapon_num[id % 3]++;
		weaponList.emplace_back(new Weapon(attack, id % 3));
		warrior_ATK = attack;
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
	Ninja(int id, int color, Headquarters* ph) :Warrior(id, lifeCost, NINJA, color, ph)
	{
		weapon_num[id % 3]++;
		weapon_num[(id + 1) % 3]++;
		weaponList.emplace_back(new Weapon(attack, id % 3));
		weaponList.emplace_back(new Weapon(attack, (id + 1) % 3));
		warrior_ATK = attack;
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
	Iceman(int id, int color, Headquarters* ph) :Warrior(id, lifeCost, ICEMAN, color, ph)
	{
		weapon_num[id % 3]++;
		weaponList.emplace_back(new Weapon(attack, id % 3));
		warrior_ATK = attack;
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
	Lion(int loyalty, int id, int color, Headquarters* ph) :loyalty(loyalty), Warrior(id, lifeCost, LION, color, ph)
	{
		weapon_num[id % 3]++;
		weaponList.emplace_back(new Weapon(attack, id % 3));
		warrior_ATK = attack;
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
	Wolf(int id, int color, Headquarters* ph) : Warrior(id, lifeCost, WOLF, color, ph) 
	{
		warrior_ATK = attack;
	}

	//抢对方武器
	Weapon* Snatch(Warrior* enemy)
	{
		//if(enemy->weaponList)
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
	bool isEnd;
public:
	Factory();
	
	//项目开始
	void Start(int& n)
	{
		Timer::InitTime();
		n++;
		head_red = new Headquarters(RED, this);
		head_blue = new Headquarters(BLUE, this);
		cout << "Case:" << n << endl;
		/* cout events */
		while ((head_red->hasLife || head_blue->hasLife) && !isEnd)
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
		/* march */
		head_red->WarriorsMarch();
		head_blue->WarriorsMarch();
		if (isEnd) return;
		Timer::UpdateMin(25);
		/* wolf */
		Timer::UpdateMin(5);
		/* battle */
		Battle_report();
		Timer::UpdateMin(10);
		head_red->HeadquartersStatus();
		head_blue->HeadquartersStatus();
		
		Timer::UpdateMin(5);
		Warriors_report();
	}

	//战斗播报
	void Battle_report()
	{
		for (int i = 1; i <= Factory::cityNum; i++)
		{
			city_list[i].Battle();
		}
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

	static City* GetCityArr() { return city_list; }

	Headquarters* GetRedHead() { return head_red; }

	Headquarters* GetBlueHead() { return head_blue; }

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

//检查战斗结果
int City::CheckResult(Warrior* r, Warrior* b)
{
	int ret = -1;
	if (r->IsDead() && !b->IsDead())
	{
		//蓝方胜利
		Timer::PrintTime();
		printf("blue %s %d killed red %s %d in city %d remaining %d elements\n",
			b_w->GetName().c_str(),
			b_w->Get_id(),
			r_w->GetName().c_str(),
			r_w->Get_id(),
			this->Get_id(),
			b_w->GetCurLife()
		);
		b->Stole(r);
		ret = 0;
	}
	else if (!r->IsDead() && b->IsDead())
	{
		//红方胜利
		Timer::PrintTime();
		printf("red %s %d killed blue %s %d in city %d remaining %d elements\n",
			r_w->GetName().c_str(),
			r_w->Get_id(),
			b_w->GetName().c_str(),
			b_w->Get_id(),
			this->Get_id(),
			r_w->GetCurLife()
		);
		r->Stole(b);
		ret = 0;
	}
	else if (r->IsDead() && b->IsDead())
	{
		//都死亡
		Timer::PrintTime();
		printf("both red %s %d and blue %s %d died in city %d\n",
			r_w->GetName().c_str(),
			r_w->Get_id(),
			b_w->GetName().c_str(),
			b_w->Get_id(),
			this->Get_id()
		);
		ret = 0;
	}
	else if (r->IsWeaponEmpty() && b->IsWeaponEmpty())
	{
		// 平局
		Timer::PrintTime();
		printf("both red %s %d and blue %s %d were alive in city %d\n",
			r_w->GetName().c_str(),
			r_w->Get_id(),
			b_w->GetName().c_str(),
			b_w->Get_id(),
			this->Get_id()
		);
		ret = 0;
	}
	return ret;
}

void City::Battle()
{
	if (r_w == NULL || b_w == NULL) return; //没有战斗发生
	
	turn = (index % 2 == 1) ? RED : BLUE; //奇数城市，红先攻击
	
	Weapon* red_weapon, * blue_weapon;
	/* 挑选武器 */
	red_weapon = r_w->SelectWeapon();
	blue_weapon = b_w->SelectWeapon();

	int ret;
	/* 战斗过程 */
	if (RED == turn)
	{
		//红方先手
		while (!r_w->IsDead() && !b_w->IsDead())
		{
			r_w->Attack(b_w);
			//红方胜利?
			ret = CheckResult(r_w, b_w);
			if (0 == ret) break;
			b_w->Attack(r_w);
			ret = CheckResult(r_w, b_w);
			if (0 == ret) break;
		}
	}
	else
	{
		//蓝方先手
		while (!r_w->IsDead() && !b_w->IsDead())
		{
			b_w->Attack(b_w);
			ret = CheckResult(r_w, b_w);
			if (0 == ret) break;
			r_w->Attack(r_w);
			ret = CheckResult(r_w, b_w);
			if (0 == ret) break;
		}
	}
		
}


City Factory::city_list[MAXCITYNUM]; //城市数组


Headquarters::Headquarters(int color, Factory* pf):color(color), hasLife(true)
	, curLifeElem(initLife), turn(0), canProduce(true),pf(pf),isOccupied(false)
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


//被占领

inline void Headquarters::beOccupied() { 
	isOccupied = true; 
	pf->isEnd = true;
	Timer::PrintTime();
	cout << this->colorName+" "<< "headquarter was taken" << endl;
}

//武士降生 0min
int Headquarters::WarriorsBirth()
{
	Warrior* w = SelectWarrior();
	if (NULL == w) return -1;
	curWarriorList.emplace_back(w);
	Timer::PrintTime();
	cout << colorName + " " << w->GetName() + " " << w->Get_id() << " born" << endl;
	if (w->Get_ID() == LION)
	{
		cout << "Its loyalty is " << w->GetLoyalty() << endl;
	}
	return 0;
}

//武士前进 10mmin
void Headquarters::WarriorsMarch()
{
	vector<Warrior*>::iterator i = curWarriorList.begin();
	for (; i != curWarriorList.end(); i++)
	{
		(*i)->March();
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
	if (!canProduce) return NULL;
	int time = Timer::GetTime();
	int id = time + 1;
	/* 判断生命值是否足够,一旦不够就停止出兵 */
	if (curLifeElem < warriorCostByOrder[turn % warriorTypeCnt])
	{
		hasLife = false;
		cout << colorName + " headquarter stops making warriors" << endl;
		canProduce = false;
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
		curWarrior = new Dragon(curLifeElem / ((float)Dragon::lifeCost), id, color, this);
		break;
	case NINJA:
		curWarrior = new Ninja(id, color, this);
		break;
	case ICEMAN:
		curWarrior = new Iceman(id, color, this);
		break;
	case LION:
		curWarrior = new Lion(curLifeElem, id, color, this); //忠诚度就是当前司令部的生命curLife
		break;
	case WOLF:
		curWarrior = new Wolf(id, color, this);
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
	else if(canProduce)
	{
		cout << colorName + " headquarter stops making warriors" << endl;
		canProduce = false;
	}
	turn++; //轮到下一个兵种
}


int main()
{
	Factory::InitProject();
	int cnt, n = 0; // cnt: 数据组数 n: 该组数据的编号
	cin >> cnt;
	Factory::InputData();
	while (cnt--)
	{
		Factory f;
		f.Start(n);
	}
	return 0;
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
		city = 0;
	}
	else
	{
		colorName = "blue";
		city = Factory::cityNum + 1;
	}
}


//攻击
void Warrior::Attack(Warrior* enemy)
{
	if (weaponList.empty()) return;
	Weapon* w = weaponList[0];
	enemy->Hurt(w->GetATK());
	if (this->Get_ID() != NINJA && w->GetType() == BOMB)
	{
		this->Hurt(w->GetATK() / 2);
	}
	
	if (w->GetUseTime() > 0)
	{
		w->UseTimeDecline();
	}

	if (0 == w->GetUseTime())
	{
		weaponList.erase(weaponList.begin());
		delete w;
	}
}

void Warrior::Stole(Warrior* enemy)
{
	int cnt = 10 - weaponList.size();
	for (int i = 0; i < cnt && i < enemy->weaponList.size(); i++)
	{
		weaponList.emplace_back(enemy->weaponList[i]);
	}
	enemy->weaponList.empty();
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

//前进

inline void Warrior::March()
{
	if (city < 0 || city > Factory::cityNum + 1) return;
	if (isDead) return;
	switch (color)
	{
	case RED:
		if (city < Factory::cityNum + 1)
		{
			city++;
			Timer::PrintTime();
			printf("red %s %d marched to city %d with %d elements and force %.0f\n",
				GetName().c_str(),
				id,
				city,
				curLife,
				warrior_ATK
			);
			if (city == Factory::cityNum + 1)
			{
				/* 占领蓝方司令部 */
				team->GetFactory()->GetBlueHead()->beOccupied();
				return;
			}
			Factory::city_list[city].SetRedWarrior(this);
			break;
		}
	case BLUE:
		if (city > 0)
		{
			city--;
			Timer::PrintTime();
			printf("blue %s %d marched to city %d with %d elements and force %.0f\n",
				GetName().c_str(),
				id,
				city,
				curLife,
				warrior_ATK
			);
			if (city == 0)
			{
				/* 占领红方司令部 */
				team->GetFactory()->GetRedHead()->beOccupied();
				return;
			}
			Factory::city_list[city].SetBlueWarrior(this);
			break;
		}
	}
}

Weapon* Warrior::SelectWeapon()
{
	if (ID == WOLF);
	if (weaponList.size() == 0) return NULL;
	sort(weaponList.begin(), weaponList.end());
	return weaponList[0];
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

inline Factory::Factory() :head_red(NULL), head_blue(NULL), isEnd(false)
{
	/* 城市初始化 */
	for (int i = 0; i <= cityNum + 1; i++)
	{
		city_list[i].SetIndex(i); //下标为0红方基地，下表为cityNum+1为蓝方基地
		city_list[i].SetBlueWarrior(NULL);
		city_list[i].SetRedWarrior(NULL);
	}
}

Weapon::Weapon(int ATK, int type):
	type(type),ATK_damage(ATK),use_cnt(0)
{
	if (SWORD == type)
	{
		ATK_damage = ATK * 0.2;
		use_cnt = INFINITY;
	}
	else if (BOMB == type)
	{
		ATK_damage = ATK * 0.4;
		use_cnt = 1;
	}
	else if (ARROW == type)
	{
		ATK_damage = ATK * 0.3;
		use_cnt = 2;
	}
}

bool Weapon::operator<(Weapon* that)
{
	if (this->type != that->type)
	{
		return this->type < that->type;
	}
	else
	{
		return this->use_cnt < that->use_cnt;
	}
}

bool Weapon::operator==(Weapon* that)
{
	if (this->type == that->type && this->use_cnt == that->use_cnt)
	{
		return true;
	}
	else
	{
		return false;
	}
}

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

//������Ŀ�Ļ���������һЩ���ú���
class Warrior;
class Factory;
class Weapon;
class Wolf;
class City
{
private:
	int index;
	int turn;
	Warrior* r_w; //�췽սʿ
	Warrior* b_w; //����սʿ
public:
	City() :r_w(NULL), b_w(NULL), turn(RED), index(0) {}

	//��������
	void SetIndex(int i){ index = i; }

	//���ú췽սʿ
	void SetRedWarrior(Warrior* r){ r_w = r; }

	//��������սʿ
	void SetBlueWarrior(Warrior* b) { b_w = b; }

	//��ó�������
	int Get_id() { return index; }

	//���ս�����,��������0,û��������-1
	int CheckResult(Warrior* r, Warrior* b);

	//�ڳ�����ս��
	void Battle();
};

/* ֻ��һ��ʱ�� */
class Timer
{
private:
	static int hour; // ��ǰСʱ
	static int min; // ��ǰ����
public:
	static int totalGameTime; //�ܹ����м�������Ϸ
	//��õ�ǰʱ��
	static int GetTime() { return hour; }
	//��ʱ���ʼ��Ϊ0
	static void InitTime() { hour = 0; min = 0; }
	//��Сʱ+1
	static void UpdateHour() { hour++; min = 0; }
	//���·��ӣ�������+min
	static void UpdateMin(int minute) { min += minute; }
	//��ӡʱ��
	static void PrintTime();
};

int Timer::hour = 0; // ��ǰʱ��
int Timer::min = 0; // ��ǰʱ��
int Timer::totalGameTime; //�ܹ����м�������Ϸ

class Headquarters
{
private:
	static const int warriorTypeCnt = 5; //���ָ���
	static const int circuCnt = 5; //ѭ������
	string order[circuCnt]; //˳��
	int turn; //�ִ�

	string curWarriorName; //��ǰʱ��Ҫ���ı���
	int curWarriorCnt[warriorTypeCnt]; //��ǰսʿ����
	vector<Warrior*> curWarriorList; //��ǰսʿ�б�

	int color;  //��=0����=1
	string colorName; //��ɫ������ɫ��

	int curLifeElem; //��ǰ˾�����Ԫ
	bool canProduce; //˾��Ƿ��������
	bool isOccupied; //�Ƿ�ռ��
public:
	vector<int> warriorCostByOrder; //��˳���սʿ����
	static int initLife; //��ʼ����
	bool hasLife; //�Ƿ�������Ԫ���Գ���
	Factory* pf; //�������
public:
	//ָ�Ӳ����캯��
	Headquarters(int color,Factory* pf);

	virtual ~Headquarters() {}

	//��õ�ǰ�Ĺ���factory
	Factory* GetFactory() { return pf; }

	//��õ�ǰ����Ԫ
	int GetLifeElem() { return curLifeElem; }

	//���õ�ǰ������Ԫ
	void SetLifeElem(int x) { curLifeElem = x; }

	//��ռ��
	void beOccupied();

	/* һ��Сʱ�ڷ������¼� */
	//��ʿ���� 0min
	int WarriorsBirth();

	//��ʿǰ�� 10mmin
	void WarriorsMarch();

	//˾�����״̬ 50min
	void HeadquartersStatus();

	//ָ�Ӳ���ʱ�����
	Warrior* SelectWarrior();

	void printEvents(Warrior* curWarrior);
};

int Headquarters::initLife;
/* ˾������ */

class Warrior
{
#define DRAGON 0
#define NINJA 1
#define ICEMAN 2
#define LION 3
#define WOLF 4
protected:
	/* սʿ���� */
	int id; //��Ϸ�еı��
	int ID; //սʿ���� 0-4
	int curLife; //��ǰ����
	float warrior_ATK; //������
	bool isDead; //�Ƿ�����

	/* ��Ӫ */
	int color;
	string colorName;
	Headquarters* team; //��Ӫָ��

	/* սʿ������ */
	vector<int> weapon_num;
	vector<Weapon*> weaponList;

	int city; //����������

	static const int warriorTypeCnt = 5; //սʿ������
public:
	/* һЩȫ�ֿ��õ���Ϣ��սʿ�б�ID-����-���� */
	static vector<int> warriorCost;  //սʿ����
	static vector<string> warriorName;  //սʿ����


	// ���캯����id
	Warrior(int id = 0, int cost = 0, int ID = 0, int color = 0, Headquarters* team = NULL);

	// ���սʿ������Vector3
	int GetWeaponNum(int type){ return weapon_num[type]; }

	// ���սʿ�ı�ţ�id��
	int Get_id() { return id; }

	// ���սʿ�����ͣ�ID��
	int Get_ID() { return ID; }

	// ���սʿ������
	string GetName() { return warriorName[ID]; }

	// ���սʿ�ĵ�ǰ����
	int GetCurLife() { return curLife; }

	// ���ʨ�ӵ��ҳ϶�
	virtual int GetLoyalty(){ return -1; }

	// �Ƿ�����
	bool IsDead() { return isDead; }

	/* ���� */
	//����
	void Die()
	{
		isDead = true;
		/* ��team��սʿ�б����Ƴ����սʿ */
	}

	//����
	void Attack(Warrior* enemy);
	
	//��������
	void Stole(Warrior* enemy);

	//����
	void Hurt(unsigned int val);

	//ǰ��
	void March();

	//��ѡ����
	Weapon* SelectWeapon();

	//û������
	bool IsWeaponEmpty() { return weaponList.empty(); }

	//��ʿ����״̬ 55min
	void WarriorsStatus();

	//���Խ�սʿ����ת��Ϊ���ͱ��ID,��������ڣ�����-1;
	static int NameToID(string name);

};

vector<int> Warrior::warriorCost;     //սʿ����
vector<string> Warrior::warriorName;   //սʿ����

/* ---------------------------������------------------------- */
class Weapon
{
#define WEAPON_NUM 3
#define INFINITY -1
public:
	/* һЩȫ�ֿ��õ���Ϣ�������б�ID-���� */
	static vector<string> weaponName;  //��������
private:
	int ATK_damage;  //������
	int use_cnt; //ʹ�ô���
	int type; //��������
public:
	Weapon(int ATK, int type);
	bool operator<(Weapon* that);
	bool operator==(Weapon* that);
	int GetATK() { return ATK_damage; }
	int GetUseTime() { return use_cnt; }
	int GetType() { return type; }

	void UseTimeDecline() { use_cnt--; }
};

vector<string> Weapon::weaponName;   //��������

/* ---------------------------���������------------------------- */

/* ---------------------------����սʿ------------------------- */
//��
class Dragon :public Warrior
{
public:
	static int lifeCost; // ���ĵ�����Ԫ
	static int ID; //��սʿ�����ͱ��ID
	static int attack; // ��սʿ�Ĺ�����
	static string tag; //���սʿ������
private:
	float morale; // ʿ����Dragon���У�ֵΪ��������˾�ʣ������Ԫ�����������ԡ���dragon���������Ԫ������
public:
	//Ĭ�Ϲ��캯������ʹ��
	Dragon(int id, int color) : morale(0), Warrior(id, lifeCost, DRAGON, color) { }
	//�����캯������ʼ��������ʿ��
	Dragon(float morale, int id, int color, Headquarters *ph) : morale(morale), Warrior(id, lifeCost, DRAGON, color, ph)
	{
		weapon_num[id % 3]++;
		weaponList.emplace_back(new Weapon(attack, id % 3));
		warrior_ATK = attack;
	}
	//���ʿ��
	float GetMorale() { return morale; }
};

//����
class Ninja :public Warrior
{
public:
	static int lifeCost; // ���ĵ�����Ԫ
	static int ID; //��սʿ�����ͱ��ID
	static int attack; // ��սʿ�Ĺ�����
	static string tag; //���սʿ������
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
//����
class Iceman :public Warrior
{
public:
	static int lifeCost; // ���ĵ�����Ԫ
	static int ID; //��սʿ�����ͱ��ID
	static int attack; // ��սʿ�Ĺ�����
	static string tag; //���սʿ������
public:
	//�����캯������ʼ��������ʿ��
	Iceman(int id, int color, Headquarters* ph) :Warrior(id, lifeCost, ICEMAN, color, ph)
	{
		weapon_num[id % 3]++;
		weaponList.emplace_back(new Weapon(attack, id % 3));
		warrior_ATK = attack;
	}
};

//ʨ��
class Lion :public Warrior
{
public:
	static int lifeCost; // ���ĵ�����Ԫ
	static int ID; //��սʿ�����ͱ��ID
	static int attack; // ��սʿ�Ĺ�����
	static string tag; //���սʿ������static
	static int loyaltyLoss; //ÿ��һ����ʧ���ҳ϶�
private:
	int loyalty; //�ҳ϶ȣ�Lion���У�ֵ���ڡ�����������˾�ʣ������Ԫ����Ŀ����
public:
	//Ĭ�Ϲ��캯������ʹ��
	Lion(int id, int color) :loyalty(0), Warrior(id, lifeCost, LION, color) { }
	//�����캯������ʼ��������ʿ��
	Lion(int loyalty, int id, int color, Headquarters* ph) :loyalty(loyalty), Warrior(id, lifeCost, LION, color, ph)
	{
		weapon_num[id % 3]++;
		weaponList.emplace_back(new Weapon(attack, id % 3));
		warrior_ATK = attack;
	}
	virtual int GetLoyalty() { return loyalty; }

	//�ҳ϶���ʧ
	void LoyaltyLoss(unsigned int val)
	{
		loyalty -= val;
	}

	//���ܣ�������
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

//��
class Wolf :public Warrior
{
public:
	static int lifeCost; // ���ĵ�����Ԫ
	static int ID; //��սʿ�����ͱ��ID
	static int attack; // ��սʿ�Ĺ�����
	static string tag; //���սʿ������
public:
	//Ĭ�Ϲ��캯����wolfû���ص�
	Wolf(int id, int color, Headquarters* ph) : Warrior(id, lifeCost, WOLF, color, ph) 
	{
		warrior_ATK = attack;
	}

	//���Է�����
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

/* ---------------------------����սʿ����------------------------- */

class Factory
{
#define MAXCITYNUM 22
public:
	static int cityNum; //��������
	static City city_list[MAXCITYNUM]; // ��������
	Headquarters* head_red, * head_blue; //˫��ָ�Ӳ�
	bool isEnd;
public:
	Factory();
	
	//��Ŀ��ʼ
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
			Timer::UpdateHour(); //����ʱ��
		}
	}

	//һ��Сʱ�ڵ��������ӡ��־
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

	//ս������
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

	//��ʼ����Ŀ
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

	//��������
	static void InputData()
	{
		cin >> Headquarters::initLife >> Factory::cityNum >>
			Lion::loyaltyLoss >> Timer::totalGameTime;
		cin >> Dragon::lifeCost >> Ninja::lifeCost
			>> Iceman::lifeCost >> Lion::lifeCost >> Wolf::lifeCost;
		cin >> Dragon::attack >> Ninja::attack
			>> Iceman::attack >> Lion::attack >> Wolf::attack;

		/* ������ʿ��� */
		Dragon::ID = 0;
		Ninja::ID = 1;
		Iceman::ID = 2;
		Lion::ID = 3;
		Wolf::ID = 4;

		/* ������ʿ���� */
		Warrior::warriorCost.clear(); //�����ϴε�����
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

int Factory::cityNum; //��������

//���ս�����
int City::CheckResult(Warrior* r, Warrior* b)
{
	int ret = -1;
	if (r->IsDead() && !b->IsDead())
	{
		//����ʤ��
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
		//�췽ʤ��
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
		//������
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
		// ƽ��
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
	if (r_w == NULL || b_w == NULL) return; //û��ս������
	
	turn = (index % 2 == 1) ? RED : BLUE; //�������У����ȹ���
	
	Weapon* red_weapon, * blue_weapon;
	/* ��ѡ���� */
	red_weapon = r_w->SelectWeapon();
	blue_weapon = b_w->SelectWeapon();

	int ret;
	/* ս������ */
	if (RED == turn)
	{
		//�췽����
		while (!r_w->IsDead() && !b_w->IsDead())
		{
			r_w->Attack(b_w);
			//�췽ʤ��?
			ret = CheckResult(r_w, b_w);
			if (0 == ret) break;
			b_w->Attack(r_w);
			ret = CheckResult(r_w, b_w);
			if (0 == ret) break;
		}
	}
	else
	{
		//��������
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


City Factory::city_list[MAXCITYNUM]; //��������


Headquarters::Headquarters(int color, Factory* pf):color(color), hasLife(true)
	, curLifeElem(initLife), turn(0), canProduce(true),pf(pf),isOccupied(false)
{

	//��ʼ��order����
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

	//��ʼ��warriorCostByOrder
	for (int i = 0; i < warriorTypeCnt; i++)
	{
		int ID = Warrior::NameToID(order[i]);
		warriorCostByOrder.emplace_back(Warrior::warriorCost[ID]);
	}
}


//��ռ��

inline void Headquarters::beOccupied() { 
	isOccupied = true; 
	pf->isEnd = true;
	Timer::PrintTime();
	cout << this->colorName+" "<< "headquarter was taken" << endl;
}

//��ʿ���� 0min
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

//��ʿǰ�� 10mmin
void Headquarters::WarriorsMarch()
{
	vector<Warrior*>::iterator i = curWarriorList.begin();
	for (; i != curWarriorList.end(); i++)
	{
		(*i)->March();
	}
}

//˾�����״̬ 50min
void Headquarters::HeadquartersStatus()
{
	Timer::PrintTime();
	printf("%d elements in %s headquarter\n",
		curLifeElem,
		colorName.c_str()
	);
}

//��ѡһ��սʿ,ʧ�ܷ���NULL
Warrior* Headquarters::SelectWarrior()
{
	if (!canProduce) return NULL;
	int time = Timer::GetTime();
	int id = time + 1;
	/* �ж�����ֵ�Ƿ��㹻,һ��������ֹͣ���� */
	if (curLifeElem < warriorCostByOrder[turn % warriorTypeCnt])
	{
		hasLife = false;
		cout << colorName + " headquarter stops making warriors" << endl;
		canProduce = false;
		return NULL;
	}

	//ѡ���ܳ��ı���
	curWarriorName = order[turn % circuCnt];
	//��Ӧ�ı���++
	int curID = Warrior::NameToID(curWarriorName);
	curWarriorCnt[curID]++;

	//����֮Դ--
	int strength = Warrior::warriorCost[curID]; //���ĵ�����Դ����սʿ������ֵ
	curLifeElem -= strength;

	/* ʵ�����ñ��� */
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
		curWarrior = new Lion(curLifeElem, id, color, this); //�ҳ϶Ⱦ��ǵ�ǰ˾�������curLife
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
	turn++; //�ֵ���һ������
}


int main()
{
	Factory::InitProject();
	int cnt, n = 0; // cnt: �������� n: �������ݵı��
	cin >> cnt;
	Factory::InputData();
	while (cnt--)
	{
		Factory f;
		f.Start(n);
	}
	return 0;
}


/* -----------------------��ʿ������ʵ��----------------------- */
// ���캯����id
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


//����
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


//����
inline void Warrior::Hurt(unsigned int val)
{
	curLife -= val;
	if (curLife < 0)
	{
		curLife = 0;
		Die();
	}
}

//ǰ��

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
				/* ռ������˾� */
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
				/* ռ��췽˾� */
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

//��ʿ����״̬ 55min

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

//���Խ�սʿ����ת��Ϊ���ͱ��ID,��������ڣ�����-1;

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
/* -----------------------��ʿ������ʵ�ֽ���----------------------- */

//��ӡʱ��
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
	/* ���г�ʼ�� */
	for (int i = 0; i <= cityNum + 1; i++)
	{
		city_list[i].SetIndex(i); //�±�Ϊ0�췽���أ��±�ΪcityNum+1Ϊ��������
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

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
	int CheckResult(Warrior* r, Warrior* b, Weapon* rw, Weapon* bw);

	//lion���ܵ���־
	void RunLog();

	//�о�����־
	void MarchLog();

	//�ڳ�����ս��
	void Battle();
	

	////����Ƿ�״̬û�б仯
	//int balance();

	//������������ 35min
	void Snatch();

	//սʿ����״̬
	void WarriorStatusLog();
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
	//ת��Ϊ����
	static int GetMin();
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

	//��ʿ����״̬ 55min
	void WarriorsReport();

	//ָ�Ӳ���ʱ�����
	Warrior* SelectWarrior();

	//�Ƴ�սʿ
	int RemoveWarrior(Warrior* w);

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
	int turn; //Ŀǰʹ����������

	/* ��Ӫ */
	int color;
	string colorName;
	Headquarters* team; //��Ӫָ��

	/* սʿ������ */
	vector<int> weapon_num;
	vector<Weapon> weaponList;

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

	// ���սʿ������
	float GetATK() { return warrior_ATK; }

	// սʿ���ڳ��б��
	int GetCityIndex() { return city; }

	// �����Ӫ����string
	const string& GetColorName() { return colorName; }

	// ���ʨ�ӵ��ҳ϶�
	virtual int GetLoyalty(){ return -1; }

	// ������������
	void SetWeaponNum(int type, int num);
	
	// �Ƴ�ĳ������
	void RemoveWeaponByType(int type);

	// ��������
	virtual Weapon* Snatch(Warrior* enemy) { return NULL; }

	//������
	virtual void Yell() {  }

	//ʨ������
	virtual void Run() {  }

	//ʨ���ҳ϶ȼ���
	virtual void LoyaltyLoss(unsigned int val) {  }

	// �Ƿ�����
	bool IsDead() { return isDead; }

	/* ���� */
	//����
	void Die();

	//����
	void Attack(Warrior* enemy, Weapon * w);
	
	//��������
	void Stole(Warrior* enemy);

	//����
	void Hurt(unsigned int val);

	//ǰ��
	void March();

	//����������
	void WeaponSort();

	//��ѡ����
	Weapon* SelectWeapon();

	//���б����Ƴ�����
	int RemoveWeapon(Weapon* w);

	//û������
	bool IsWeaponEmpty() { return weaponList.empty(); }

	//��ʿ����״̬ 55min
	void WarriorsStatus();

	//���Խ�սʿ����ת��Ϊ���ͱ��ID,��������ڣ�����-1;
	static int NameToID(string name);

	friend class Wolf;
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
	bool operator<(const Weapon& that) const;
	bool operator==(const Weapon& that) const;
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
		weaponList.emplace_back(Weapon(attack, id % 3));
		warrior_ATK = attack;
	}
	//���ʿ��
	float GetMorale() { return morale; }

	//������
	virtual void Yell()
	{
		if (isDead) return;
		Timer::PrintTime();
		printf("%s %s %d yelled in city %d\n",
			GetColorName().c_str(),
			GetName().c_str(),
			id,
			city
		);
	}
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
		weaponList.emplace_back(Weapon(attack, id % 3));
		weaponList.emplace_back(Weapon(attack, (id + 1) % 3));
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
		weaponList.emplace_back(Weapon(attack, id % 3));
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
		weaponList.emplace_back(Weapon(attack, id % 3));
		warrior_ATK = attack;
	}
	virtual int GetLoyalty() { return loyalty; }

	//�ҳ϶���ʧ
	void LoyaltyLoss(unsigned int val)
	{
		loyalty -= val;
	}

	//���ܣ�������
	virtual void Run()
	{
		if (loyalty <= 0)
		{
			Die();
			Timer::PrintTime();
			printf("%s lion %d ran away\n",
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
	Wolf(int id, int color, Headquarters* ph);

	//���Է�����
	Weapon* Snatch(Warrior* enemy);
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
		cout << "Case " << n << ":" << endl;
		/* cout events */
		while (!isEnd && Timer::GetMin()<Timer::totalGameTime)
		{
			Update();
			Timer::UpdateHour(); //����ʱ��
		}
	}

	//һ��Сʱ�ڵ��������ӡ��־
	void Update()
	{
		// ��������
		head_red->WarriorsBirth();
		head_blue->WarriorsBirth();
		Timer::UpdateMin(5);
		if (Timer::GetMin() > Timer::totalGameTime) return;
		
		/* lion run */
		RunReport();
		Timer::UpdateMin(5);
		if (Timer::GetMin() > Timer::totalGameTime) return;
		
		/* march */
		head_red->WarriorsMarch();
		head_blue->WarriorsMarch();
		MarchReport();
		if (isEnd) return;
		Timer::UpdateMin(25);
		if (Timer::GetMin() > Timer::totalGameTime) return;
		
		/* wolf */
		WolfSnatchReport();
		Timer::UpdateMin(5);
		if (Timer::GetMin() > Timer::totalGameTime) return;
		
		/* battle 40min*/
		Battle_report();
		Timer::UpdateMin(10);
		if (Timer::GetMin() > Timer::totalGameTime) return;

		//ָ�Ӳ�״̬����
		head_red->HeadquartersStatus();
		head_blue->HeadquartersStatus();
		
		//սʿ״̬����
		Timer::UpdateMin(5);
		WarriorReport();
	}

	//ʨ�����ܲ���
	void RunReport()
	{
		for (int i = 0; i <= Factory::cityNum + 1; i++)
		{
			city_list[i].RunLog();
		}
	}

	//�о�����
	void MarchReport()
	{
		for (int i = 0; i <= Factory::cityNum+1; i++)
		{
			city_list[i].MarchLog();
		}
	}

	//ս������
	void Battle_report()
	{
		for (int i = 1; i <= Factory::cityNum; i++)
		{
			city_list[i].Battle();
		}
	}

	//սʿ����
	void WarriorReport()
	{
		for (int i = 1; i <= Factory::cityNum; i++)
		{
			city_list[i].WarriorStatusLog();
		}
	}

	//������
	void WolfSnatchReport()
	{
		for (int i = 1; i <= Factory::cityNum; i++)
		{
			city_list[i].Snatch();
		}
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
int City::CheckResult(Warrior* r, Warrior* b, Weapon* rw, Weapon* bw)
{
	int ret = -1;
	if (r->IsDead() && !b->IsDead())
	{
		//����ʤ��
		Timer::PrintTime();
		printf("blue %s %d killed red %s %d in city %d remaining %d elements\n",
			b->GetName().c_str(),
			b->Get_id(),
			r->GetName().c_str(),
			r->Get_id(),
			this->Get_id(),
			b->GetCurLife()
		);
		b->Stole(r);
		ret = 0;
	}
	else if (!r->IsDead() && b->IsDead())
	{
		//�췽ʤ��
		Timer::PrintTime();
		printf("red %s %d killed blue %s %d in city %d remaining %d elements\n",
			r->GetName().c_str(),
			r->Get_id(),
			b->GetName().c_str(),
			b->Get_id(),
			this->Get_id(),
			r->GetCurLife()
		);
		r->Stole(b);
		ret = 0;
	}
	else if (r->IsDead() && b->IsDead())
	{
		//������
		Timer::PrintTime();
		printf("both red %s %d and blue %s %d died in city %d\n",
			r->GetName().c_str(),
			r->Get_id(),
			b->GetName().c_str(),
			b->Get_id(),
			this->Get_id()
		);
		ret = 0;
	}
	else if ((r->IsWeaponEmpty() && b->IsWeaponEmpty()) || 
		(rw && rw->GetATK() == 0 && bw && bw->GetATK() == 0) ||
		(r->IsWeaponEmpty() && bw && bw->GetATK() == 0) ||
		(rw && rw->GetATK() == 0 && b->IsWeaponEmpty())
		)
	{
		// ƽ��
		Timer::PrintTime();
		printf("both red %s %d and blue %s %d were alive in city %d\n",
			r->GetName().c_str(),
			r->Get_id(),
			b->GetName().c_str(),
			b->Get_id(),
			this->Get_id()
		);
		ret = 0;
	}
	return ret;
}

void City::RunLog()
{
	if (r_w)
	{
		r_w->Run();
	}
	if (b_w)
	{
		b_w->Run();
	}
}

void City::MarchLog()
{
	if (r_w)
	{
		Timer::PrintTime();
		printf("red %s %d marched to city %d with %d elements and force %.0f\n",
			r_w->GetName().c_str(),
			r_w->Get_id(),
			r_w->GetCityIndex(),
			r_w->GetCurLife(),
			r_w->GetATK()
		);
	}
	if (b_w)
	{
		Timer::PrintTime();
		printf("blue %s %d marched to city %d with %d elements and force %.0f\n",
			b_w->GetName().c_str(),
			b_w->Get_id(),
			b_w->GetCityIndex(),
			b_w->GetCurLife(),
			b_w->GetATK()
		);
	}
}

void City::Battle()
{
	if (r_w == NULL || b_w == NULL) return; //û��ս������
	
	Warrior* r_w = this->r_w, * b_w = this->b_w;
	turn = (index % 2 == 1) ? RED : BLUE; //�������У����ȹ���
	
	Weapon* red_weapon, * blue_weapon;

	//����
	r_w->WeaponSort();
	b_w->WeaponSort();

	int ret;
	/* ս������ */
	if (RED == turn)
	{
		//�췽����
		while (!r_w->IsDead() && !b_w->IsDead())
		{
			red_weapon = r_w->SelectWeapon();
			blue_weapon = b_w->SelectWeapon();
			r_w->Attack(b_w, red_weapon);
			//�췽ʤ��?
			ret = CheckResult(r_w, b_w, red_weapon, blue_weapon);
			if (0 == ret) break;
			b_w->Attack(r_w, blue_weapon);
			ret = CheckResult(r_w, b_w, red_weapon, blue_weapon);
			if (0 == ret) break;
		}
	}
	else
	{
		//��������
		while (!r_w->IsDead() && !b_w->IsDead())
		{
			red_weapon = r_w->SelectWeapon();
			blue_weapon = b_w->SelectWeapon();
			b_w->Attack(r_w, blue_weapon);
			ret = CheckResult(r_w, b_w, red_weapon, blue_weapon);
			if (0 == ret) break;
			r_w->Attack(b_w, red_weapon);
			ret = CheckResult(r_w, b_w, red_weapon, blue_weapon);
			if (0 == ret) break;
		}
	}
	
	/* ���� */
	if(r_w) r_w->Yell();
	if(b_w) b_w->Yell();
}

void City::Snatch()
{
	if (r_w == NULL || b_w == NULL) return;
	/* ���������� */
	r_w->WeaponSort();
	b_w->WeaponSort();

	/* �����wolfҪ������ */
	if (r_w->Get_ID() == WOLF && b_w->Get_ID() != WOLF)
	{
		r_w->Snatch(b_w);
	}
	else if (r_w->Get_ID() != WOLF && b_w->Get_ID() == WOLF)
	{
		b_w->Snatch(r_w);
	}
}

void City::WarriorStatusLog()
{
	if (r_w )
	{
		Timer::PrintTime();
		printf("%s %s %d has %d sword %d bomb %d arrow and %d elements\n",
			r_w->GetColorName().c_str(),
			r_w->GetName().c_str(),
			r_w->Get_id(),
			r_w->GetWeaponNum(SWORD),
			r_w->GetWeaponNum(BOMB),
			r_w->GetWeaponNum(ARROW),
			r_w->GetCurLife()
		);
	}
	if (b_w)
	{
		Timer::PrintTime();
		printf("%s %s %d has %d sword %d bomb %d arrow and %d elements\n",
			b_w->GetColorName().c_str(),
			b_w->GetName().c_str(),
			b_w->Get_id(),
			b_w->GetWeaponNum(SWORD),
			b_w->GetWeaponNum(BOMB),
			b_w->GetWeaponNum(ARROW),
			b_w->GetCurLife()
		);
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

void Headquarters::WarriorsReport()
{
	vector<Warrior*>::iterator i = curWarriorList.begin();
	for (; i != curWarriorList.end(); i++)
	{
		(*i)->WarriorsStatus();
	}
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

int Headquarters::RemoveWarrior(Warrior* w)
{
	if (w == NULL || curWarriorList.empty()) return -1;
	vector<Warrior*>::iterator i = curWarriorList.begin();
	for (; i != curWarriorList.end(); i++)
	{
		if (w->Get_id() == (*i)->Get_id())
		{
			curWarriorList.erase(i);
			return 0;
		}
	}
	return -1;
}

void Headquarters::printEvents(Warrior *curWarrior)
{
	if (hasLife)
	{
		WarriorsBirth();
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
	isDead(false), team(team), turn(0)
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



/* ���� */
//����

void Warrior::SetWeaponNum(int type, int num)
{
	weapon_num[type] = num;
}

void Warrior::RemoveWeaponByType(int type)
{
	if (IsWeaponEmpty()) return;
	vector<Weapon>::iterator i = weaponList.begin();
	for (; i != weaponList.end(); i++)
	{
		if ((*i).GetType() == type)
		{
			RemoveWeapon(&(*i));
		}
	}
}

inline void Warrior::Die()
{
	isDead = true;
	/* ��team��սʿ�б����Ƴ����սʿ */
	team->RemoveWarrior(this);
	if (RED == color)
	{
		team->pf->city_list[city].SetRedWarrior(NULL);
	}
	else
	{
		team->pf->city_list[city].SetBlueWarrior(NULL);
	}
}

//����
void Warrior::Attack(Warrior* enemy, Weapon * w)
{
	if (weaponList.empty()) return;
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
		RemoveWeapon(w);
	}
}

void Warrior::Stole(Warrior* enemy)
{
	enemy->WeaponSort();
	int cnt = 10 - weaponList.size();
	for (int i = 0; i < cnt && i < enemy->weaponList.size(); i++)
	{
		weaponList.emplace_back(enemy->weaponList[i]);
		weapon_num[enemy->weaponList[i].GetType()]++;
	}
	enemy->weaponList.clear();
}


//����
inline void Warrior::Hurt(unsigned int val)
{
	curLife -= val;
	if (curLife <= 0)
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
	if (Get_ID() == ICEMAN) curLife -= curLife / 10;
	if (Get_ID() == LION)
	{
		LoyaltyLoss(Lion::loyaltyLoss);
	}
	switch (color)
	{
	case RED:
		if (city < Factory::cityNum + 1)
		{
			team->pf->city_list[city].SetRedWarrior(NULL);
			city++;
			if (city == Factory::cityNum + 1)
			{
				/* ռ������˾� */
				Timer::PrintTime();
				printf("%s %s %d reached blue headquarter with %d elements and force %.0f\n",
					colorName.c_str(),
					GetName().c_str(),
					id,
					GetCurLife(),
					GetATK()
				);
				team->GetFactory()->GetBlueHead()->beOccupied();
				return;
			}
			Factory::city_list[city].SetRedWarrior(this);
			break;
		}
	case BLUE:
		if (city > 0)
		{
			team->pf->city_list[city].SetBlueWarrior(NULL);
			city--;
			if (city == 0)
			{
				/* ռ��췽˾� */
				Timer::PrintTime();
				printf("%s %s %d reached red headquarter with %d elements and force %.0f\n",
					colorName.c_str(),
					GetName().c_str(),
					id,
					GetCurLife(),
					GetATK()
				);
				team->GetFactory()->GetRedHead()->beOccupied();
				return;
			}
			Factory::city_list[city].SetBlueWarrior(this);
			break;
		}
	}
}

void Warrior::WeaponSort()
{
	if (weaponList.empty()) return;
	sort(weaponList.begin(), weaponList.end());
}

Weapon* Warrior::SelectWeapon()
{
	if (weaponList.size() == 0) return NULL;
	Weapon ret = weaponList[turn++];
	if (weaponList.size() == turn) turn = 0;
	return &ret;
}

int Warrior::RemoveWeapon(Weapon* w)
{
	if (NULL == w || weaponList.empty()) return -1;
	vector<Weapon>::iterator i = weaponList.begin();
	for (; i != weaponList.end(); i++)
	{
		if (w == &(*i))
		{
			weaponList.erase(i);
			weapon_num[w->GetType()]--;
			turn--;
			if (-1 == turn) turn = weaponList.size() - 1;
			delete w;
			return 0;
		}
	}
	return -1;
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

int Timer::GetMin()
{
	return hour * 60 + min;
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

bool Weapon::operator<(const Weapon& that) const
{
	if (this->type != that.type)
	{
		return this->type < that.type;
	}
	else
	{
		return this->use_cnt < that.use_cnt;
	}
}

bool Weapon::operator==(const Weapon& that) const
{
	if (this->type == that.type && this->use_cnt == that.use_cnt)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//Ĭ�Ϲ��캯����wolfû���ص�

inline Wolf::Wolf(int id, int color, Headquarters* ph) : Warrior(id, lifeCost, WOLF, color, ph)
{
	warrior_ATK = attack;
}

//���Է�����

inline Weapon* Wolf::Snatch(Warrior* enemy)
{
	if (enemy->weaponList.empty()) return NULL;
	
	enemy->WeaponSort();
	int i;
	int type = enemy->weaponList[0].GetType(); //Ҫ��������
	int max = 10 - weaponList.size(); //���������
	int cnt = enemy->GetWeaponNum(type); //Ҫ���������м���
	if (type == SWORD || type == BOMB || (type == ARROW && cnt <= max))
	{
		for (i = 0; i < cnt && i < max; i++)
		{
			weaponList.emplace_back(enemy->weaponList[i]);
			enemy->weaponList.erase(enemy->weaponList.begin());
		}
	}
	else
	{
		int off = 0; //ƫ����,������ù���arrow�Ͳ���ɾ��
		for (i = 0; i < cnt && i < max; i++)
		{
			if (enemy->weaponList[i].GetUseTime() == 1) {
				i--;
				off++;
				continue; //�ù��Ĳ�Ҫ
			}
			weaponList.emplace_back(enemy->weaponList[i]);
			enemy->weaponList.erase(enemy->weaponList.begin() + off);
		}
	}
	weapon_num[type] += i;
	enemy->weapon_num[type] -= i;
	Timer::PrintTime();
	printf("%s %s %d took %d %s from %s %s %d in city %d\n",
		colorName.c_str(),
		warriorName[ID].c_str(),
		id,
		i,
		Weapon::weaponName[type].c_str(),
		enemy->colorName.c_str(),
		enemy->GetName().c_str(),
		enemy->Get_id(),
		city
	);
}

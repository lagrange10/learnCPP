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

//������Ŀ�Ļ���������һЩ���ú���
class Warrior;
class City
{
private:
	int index;
	int turn;
	Warrior* r_w; //�췽սʿ
	Warrior* b_w; //����սʿ
public:
	City() :r_w(NULL), b_w(NULL), turn(RED), index(0) {}
	void setIndex(int i){ index = i; }
	void setWarrior(Warrior* r, Warrior* b){ r_w = r; b_w = b; }
	void battle();
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

	int color;  //��=0����=1
	string colorName; //��ɫ������ɫ��

	int curLifeElem; //��ǰ˾�����Ԫ
	bool isEnd; //˾��Ƿ��������
public:
	vector<int> warriorCostByOrder; //��˳���սʿ����
	static int initLife; //��ʼ����
	bool hasLife; //�Ƿ�������Ԫ���Գ���

public:
	//ָ�Ӳ����캯��
	Headquarters(int color);

	virtual ~Headquarters() {}

	//��õ�ǰ����Ԫ
	int GetLifeElem() { return curLifeElem; }

	//���õ�ǰ������Ԫ
	void SetLifeElem(int x) { curLifeElem = x; }

	/* һ��Сʱ�ڷ������¼� */
	//��ʿ���� 0min
	void WarriorsBirth();

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
	float attack; //������
	bool isDead; //�Ƿ�����

	/* ��Ӫ */
	int color;
	string colorName;
	Headquarters* team; //��Ӫָ��

	/* սʿ�������� */
	vector<int> weapon_num;


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

	/* ���� */
	//����
	void Die()
	{
		isDead = true;
		/* ��team��սʿ�б����Ƴ����սʿ */
	}

	//����
	void Hurt(unsigned int val);

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
public:
	/* һЩȫ�ֿ��õ���Ϣ�������б�ID-���� */
	static vector<string> weaponName;  //��������

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
	Dragon(float morale, int id, int color) : morale(morale), Warrior(id, lifeCost, DRAGON, color)
	{
		weapon_num[id % 3]++;
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
	Ninja(int id, int color) :Warrior(id, lifeCost, NINJA, color)
	{
		weapon_num[id % 3]++;
		weapon_num[(id + 1) % 3]++;
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
	Iceman(int id, int color) :Warrior(id, lifeCost, ICEMAN, color)
	{
		weapon_num[id % 3]++;
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
	Lion(int loyalty, int id, int color) :loyalty(loyalty), Warrior(id, lifeCost, LION, color)
	{
		weapon_num[id % 3]++;
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

/* ---------------------------����սʿ����------------------------- */


class Factory
{
#define MAXCITYNUM 22
public:
	static int cityNum; //��������
	static City city_list[MAXCITYNUM]; // ��������
	Headquarters* head_red, * head_blue; //˫��ָ�Ӳ�
public:
	Factory();
	
	//��Ŀ��ʼ
	void Start(int& n)
	{
		Timer::InitTime();
		n++;
		InputData(); //��������
		head_red = new Headquarters(RED);
		head_blue = new Headquarters(BLUE);
		cout << "Case:" << n << endl;
		//cout events
		while (head_red->hasLife || head_blue->hasLife)
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


void City::battle()
{
	turn = (index % 2 == 1) ? RED : BLUE; //�������У����ȹ���
		
	/* ս������ */
	if (RED == turn)
	{

	}
	else
	{

	}
		
}


City Factory::city_list[MAXCITYNUM]; //��������


Headquarters::Headquarters(int color) :color(color), hasLife(true)
	, curLifeElem(initLife), turn(0), isEnd(false)
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

//��ʿ���� 0min
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
	if (isEnd) return NULL;
	int time = Timer::GetTime();
	int id = time + 1;
	/* �ж�����ֵ�Ƿ��㹻,һ��������ֹͣ���� */
	if (curLifeElem < warriorCostByOrder[turn % warriorTypeCnt])
	{
		hasLife = false;
		cout << colorName + " headquarter stops making warriors" << endl;
		isEnd = true;
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
		curWarrior = new Dragon(curLifeElem / ((float)Dragon::lifeCost), id, color);
		break;
	case NINJA:
		curWarrior = new Ninja(id, color);
		break;
	case ICEMAN:
		curWarrior = new Iceman(id, color);
		break;
	case LION:
		curWarrior = new Lion(curLifeElem, id, color); //�ҳ϶Ⱦ��ǵ�ǰ˾�������curLife
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
	turn++; //�ֵ���һ������
}


int main()
{
	Factory::InitProject();
	int cnt, n = 0; // cnt: �������� n: �������ݵı��
	cin >> cnt;
	while (cnt--)
	{
		Factory f;
		f.Start(n);
	}
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
	}
	else
	{
		colorName = "blue";
	}
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

inline Factory::Factory() :head_red(NULL), head_blue(NULL)
{
	/* ���г�ʼ������ */
	for (int i = 0; i <= cityNum + 1; i++)
	{
		city_list[i].setIndex(i); //�±�Ϊ0�췽���أ��±�ΪcityNum+1Ϊ��������
	}
}

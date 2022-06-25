#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdio>
#include <cstdlib>
using namespace std;

//������Ŀ�Ļ���������һЩ���ú���
class Factory
{
public:
	static int cityNum; //��������
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

int Factory::cityNum; //��������

class Warrior
{
#define DRAGON 0
#define NINJA 1
#define ICEMAN 2
#define LION 3
#define WOLF 4
protected:
	/* սʿ���� */
	int id; //��Ϸ�еı�� ID�����ͱ�ţ������±�
	int curLife; //��ǰ����
	float attack; //������

	/* սʿ�������� */
	vector<int> weapon_num;
	int arrow_no_use; //û�ù���arrow��������arrow_num-1һ��
	
	
	static const int warriorTypeCnt = 5; //սʿ������
public:
	/* һЩȫ�ֿ��õ���Ϣ��սʿ�б�ID-����-���� */
	static vector<int> warriorCost;  //սʿ����
	static vector<string> warriorName;  //սʿ����


	// ���캯����id
	Warrior(int id) :id(id) 
	{ 
		for (int i = 0; i < 3; i++) weapon_num.emplace_back(0);
	}

	Warrior(int id,int cost) :id(id),curLife(cost)
	{
		for (int i = 0; i < 3; i++) weapon_num.emplace_back(0);
	}

	// ���սʿ������Vector3
	vector<int>& GetWeapon(vector<int>& v)
	{
		v = weapon_num;
		return v;
	}

	// ���սʿ�ı�ţ�id��
	int GetID() { return id; }

	// ���սʿ�ĵ�ǰ����
	int GetCurLife() { return curLife; }

	//���Խ�սʿ����ת��Ϊ���ͱ��ID,��������ڣ�����-1;
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
	Dragon(int id): morale(0), Warrior(id,lifeCost){ }
	//�����캯������ʼ��������ʿ��
	Dragon(float morale, int id): morale(morale), Warrior(id,lifeCost) 
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
	Ninja(int id):Warrior(id, lifeCost)
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
	Iceman(int id) :Warrior(id, lifeCost)
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
	Lion(int id) :loyalty(0), Warrior(id, lifeCost) { }
	//�����캯������ʼ��������ʿ��
	Lion(int loyalty,int id) :loyalty(loyalty), Warrior(id, lifeCost)
	{
		weapon_num[id % 3]++;
	}
	int GetLoyalty() { return loyalty; }
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

/* ---------------------------����սʿ����------------------------- */

//ֻ��һ��ʱ��
class Timer
{
private:
	static int now; // ��ǰʱ��
public:
	static int totalGameTime; //�ܹ����м�������Ϸ
	//��õ�ǰʱ��
	static int GetTime() { return now; }
	//��ʱ���ʼ��Ϊ0
	static void InitTime() { now = 0; }
	//��ʱ��+1
	static void UpdateTime() { now++; }
};

int Timer::now = 0; // ��ǰʱ��
int Timer::totalGameTime; //�ܹ����м�������Ϸ
//˾�
class Headquarters
{
private:


	static const int warriorTypeCnt = 5; //���ָ���
	static const int circuCnt = 5; //ѭ������
	string order[circuCnt]; //˳��
	int turn; //�ִ�

	string curWarrior; //��ǰʱ��Ҫ���ı���
	int curWarriorCnt[warriorTypeCnt]; //��ǰսʿ����
	string name; //��ɫ������ɫ��
	int curLife; //��ǰ˾�����
	bool end;
public:
	vector<int> warriorCostByOrder; //��˳���սʿ����
	static int initLife; //��ʼ����
	bool hasLife; //�Ƿ�������Ԫ���Գ���

	//ָ�Ӳ����캯��
	Headquarters(string name) :name(name), hasLife(true)
		, curLife(initLife), turn(0), end(false)
	{
		//��ʼ��order����
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

		//��ʼ��warriorCostByOrder
		for (int i = 0; i < warriorTypeCnt; i++)
		{
			int ID = Warrior::NameToID(order[i]);
			warriorCostByOrder.emplace_back(Warrior::warriorCost[ID]);
		}
	}

	virtual ~Headquarters() {}

	int getLife() { return curLife; }

	void setLife(int x) { curLife = x; }

	//ָ�Ӳ���ʱ�����
	void Update()
	{
		if (end) return;
		int time = Timer::GetTime();
		int id = time + 1;
		//�ж�����ֵ�Ƿ��㹻��ѡ���һ���ܳ��ı���
		int cnt = warriorTypeCnt; //�����������Գ���5���Ժ������ѭ��
		while (curLife < warriorCostByOrder[turn % warriorTypeCnt])
		{
			turn++; cnt--;
			if (cnt == 0)
			{
				hasLife = false;
				break;
			}
		}

		//ѡ���ܳ��ı���
		curWarrior = order[turn % circuCnt];
		//��Ӧ�ı���++
		int curID = Warrior::NameToID(curWarrior);
		curWarriorCnt[curID]++;

		//����֮Դ--
		int strength = Warrior::warriorCost[curID]; //���ĵ�����Դ����սʿ������ֵ
		curLife -= strength;

		/* ʵ�����ñ��� */
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
			war_list[LION] = new Lion(curLife, id); //�ҳ϶Ⱦ��ǵ�ǰ˾�������curLife
			break;
		case WOLF:
			war_list[WOLF] = new Wolf(id);
			break;
		default:
			break;
		}

		/* ����������� */
		vector<int> weapon_num;
		war_list[curID]->GetWeapon(weapon_num);
		//��ӡ������Ϣ
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
		turn++; //�ֵ���һ������
	}
};

int Headquarters::initLife;

class Input
{
public:
	//��Ŀ��ʼ������һЩ��̬������ֵ
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
};

int main()
{
	Input::InitProject();
	int cnt, n = 0; // cnt: �������� n: �������ݵı��
	cin >> cnt;
	while (cnt--)
	{
		Timer::InitTime();
		n++;
		Input::InputData(); //��������
		Headquarters red("red"), blue("blue");
		cout << "Case:" << n << endl;
		//cout events
		while (red.hasLife || blue.hasLife)
		{
			red.Update();
			blue.Update();
			Timer::UpdateTime(); //����ʱ��
		}
	}


}
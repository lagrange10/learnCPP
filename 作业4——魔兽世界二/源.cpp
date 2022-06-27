#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdio>
#include <cstdlib>
using namespace std;
//һЩ���ú���
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
	/* սʿ���� */
	int id; //��Ϸ�еı�� ID�����ͱ�ţ������±�
	
	int curLife; //��ǰ����

	static const int warriorTypeCnt = 5;
public:
	/* һЩȫ�ֿ��õ���Ϣ��սʿ�б�ID-����-���� */
	static vector<int> warriorCost;  //սʿ����
	static vector<string> warriorName;  //սʿ����

	// ���캯����id
	Warrior() :id(0) {}
	Warrior(int id):id(id) {}

	// ���սʿ�ı�ţ�id��
	int Get_id() { return id; }

	//���Խ�սʿ����ת��Ϊ���ͱ��ID,��������ڣ�����-1;
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

vector<int> Warrior::warriorCost;     //սʿ����
vector<string> Warrior::warriorName;   //սʿ����

/* ---------------------------������------------------------- */
class Weapon
{
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
	static string tag; //���սʿ������
private:
	int weaponID; // ӵ�е�������ţ��Լ�����ʱ���Ϊn������Ϊn%3
	float morale; // ʿ����Dragon���У�ֵΪ��������˾�ʣ������Ԫ�����������ԡ���dragon���������Ԫ������
public:
	//Ĭ�Ϲ��캯������ʹ��
	Dragon():weaponID(0), morale(0){ }
	//�����캯������ʼ��������ʿ��
	Dragon(int weaponID, float morale, int id):weaponID(weaponID), morale(morale), Warrior(id){}
	//����������
	int GetWeaponID() { return weaponID; }
	//�����������
	string GetWeaponName(int ID) { return Weapon::weaponName[ID]; }
	//���ʿ��
	float GetMorale() { return morale; }
};

//����
class Ninja :public Warrior
{
public:
	static int lifeCost; // ���ĵ�����Ԫ
	static int ID; //��սʿ�����ͱ��ID
	static string tag; //���սʿ������
private:
	int weaponID1; // ӵ�е��������1���Լ�����ʱ���Ϊn������Ϊn%3
	int weaponID2; // ӵ�е��������2���Լ�����ʱ���Ϊn������Ϊ��n+1��%3
public:
	//Ĭ�Ϲ��캯������ʹ��
	Ninja():weaponID1(0), weaponID2(0) { }
	//�����캯������ʼ��������ʿ��
	Ninja(int weaponID1, int weaponID2) :weaponID1(weaponID1), weaponID2(weaponID2){}
	//����������1
	int GetWeaponID1() { return weaponID1; }
	//����������2
	int GetWeaponID2() { return weaponID2; }
	//�����������
	string GetWeaponName(int ID) { return Weapon::weaponName[ID]; }
};
//����
class Iceman :public Warrior
{
public:
	static int lifeCost; // ���ĵ�����Ԫ
	static int ID; //��սʿ�����ͱ��ID
	static string tag; //���սʿ������
private:
	int weaponID; // ӵ�е�������ţ��Լ�����ʱ���Ϊn������Ϊn%3
public:
	//Ĭ�Ϲ��캯������ʹ��
	Iceman():weaponID(0) { }
	//�����캯������ʼ��������ʿ��
	Iceman(int weaponID) :weaponID(weaponID) {}
	//����������
	int GetWeaponID() { return weaponID; }
	//�����������
	string GetWeaponName(int ID) { return Weapon::weaponName[ID]; }
};

//ʨ��
class Lion :public Warrior
{
public:
	static int lifeCost; // ���ĵ�����Ԫ
	static int ID; //��սʿ�����ͱ��ID
	static string tag; //���սʿ������
private:
	int loyalty; //�ҳ϶ȣ�Lion���У�ֵ���ڡ�����������˾�ʣ������Ԫ����Ŀ����
public:
	//Ĭ�Ϲ��캯������ʹ��
	Lion():loyalty(0) { }
	//�����캯������ʼ��������ʿ��
	Lion(int loyalty) :loyalty(loyalty) {}
	int GetLoyalty() { return loyalty; }
};

//��
class Wolf :public Warrior
{
public:
	static int lifeCost; // ���ĵ�����Ԫ
	static int ID; //��սʿ�����ͱ��ID
	static string tag; //���սʿ������
public:
	//Ĭ�Ϲ��캯����wolfû���ص�
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

/* ---------------------------����սʿ����------------------------- */

//ֻ��һ��ʱ��
class Timer
{
private:
	static int now; // ��ǰʱ��
public:
	//��õ�ǰʱ��
	static int GetTime() { return now; }
	//��ʱ���ʼ��Ϊ0
	static void InitTime() { now = 0; }
	//��ʱ��+1
	static void UpdateTime() { now++; }
};

int Timer::now = 0; // ��ǰʱ��

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
	string colorName; //��ɫ������ɫ��
	int curLifeElem; //��ǰ˾�����
	bool isEnd;
public:
	vector<int> warriorCostByOrder; //��˳���սʿ����
	static int initLife; //��ʼ����
	bool hasLife; //�Ƿ�������Ԫ���Գ���

	//ָ�Ӳ����캯��
	Headquarters(string name) :colorName(name), hasLife(true)
		, curLifeElem(initLife), turn(0), isEnd(false)
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

	int GetLifeElem() { return curLifeElem; }

	void SetLifeElem(int x) { curLifeElem = x; }

	//ָ�Ӳ���ʱ�����
	void Update()
	{
		if (isEnd) return;
		int time = Timer::GetTime();
		int id = time + 1;
		//�ж�����ֵ�Ƿ��㹻��ѡ���һ���ܳ��ı���
		int cnt = warriorTypeCnt; //�����������Գ���5���Ժ������ѭ��
		while (curLifeElem < warriorCostByOrder[turn % warriorTypeCnt])
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
		curLifeElem -= strength;

		/* ʵ�����ñ��� */
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
		cin >> Headquarters::initLife;
		cin >> Dragon::lifeCost >> Ninja::lifeCost
			>> Iceman::lifeCost >> Lion::lifeCost >> Wolf::lifeCost;
		
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
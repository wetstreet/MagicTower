#ifndef MANAGER_H
#define MANAGER_H

#include <Windows.h>
#include "object.h"
#include "player.h"
#include "enemy.h"
#include "map.h"

const int M_OBJECT = 0;
const int M_PLAYER = 1;
const int M_ENEMY = 2;

//��㱣��object�����object���а���λͼ����Ӧ������
struct node{
	//Ĭ�Ϲ��캯��������ͷ���ʱ��Ҫ�õ�
	node(node *p = nullptr){ next = p; }
	//��Ϊ���������Ҫ���м���룬ֻ����������ӣ������ڹ��캯����ֱ��Ϊnext����ֵ
	node(int id, UINT resourceId, int type, HINSTANCE hIns){
		if (type == M_ENEMY)
			data = new Enemy(id, resourceId, hIns);
		else if (type == M_PLAYER)
			data = new Player(id, resourceId, hIns);
		else
			data = new Object(id, resourceId, hIns);
		next = nullptr;
	}
	Object *data;
	node *next;
};

//manager����Ϊ���������
class Manager{
public:
	Manager(HINSTANCE hIns = nullptr) :hInstance(hIns), length(0){ head = new node; Initialize(); }
	void Initialize();
	~Manager(){ clear(); }
	void clear();
	Object *Search(int);
	int	getLength(){ return length; }
	HINSTANCE getHIns()const{ return hInstance; }
	Player *getPlayer(){ return (Player*)Search(PLAYER); }
	bool addElement(int id, UINT resourceId, int type);
	bool calcDamage(Enemy *enemy);
	void Fight(HWND, int, int, int);
	void DrawMap(HDC hdc, MapManager *mm);
	void PrintInfo(HDC hdc);
private:
	int length;
	node *head;
	HINSTANCE hInstance;
};

void Manager::Initialize()
{
	addElement(-2, IDB_PLAYER, M_PLAYER);
	addElement(-1, IDB_BACKGROUND, M_OBJECT);
	addElement(1, IDB_WALL, M_OBJECT);
	addElement(2, IDB_UPSTAIRS, M_OBJECT);
	addElement(3, IDB_DOWNSTAIRS, M_OBJECT);
	addElement(4, IDB_DOOR, M_OBJECT);
	addElement(5, IDB_KEY, M_OBJECT);
	addElement(6, IDB_SHOP, M_OBJECT);
	addElement(7, IDB_BLUEGEM, M_OBJECT);
	addElement(8, IDB_REDGEM, M_OBJECT);
	addElement(9, IDB_SMALLMED, M_OBJECT);
	addElement(10, IDB_BIGMED, M_OBJECT);
	addElement(11, IDB_GREENSLIME, M_ENEMY);
	addElement(12, IDB_REDSLIME, M_ENEMY);
	addElement(13, IDB_BLACKSLIME, M_OBJECT);
	addElement(14, IDB_SKELETON, M_OBJECT);
	addElement(15, IDB_SKELETONSOLDIER, M_OBJECT);
	addElement(16, IDB_SKELETONCAPTAIN, M_OBJECT);
	addElement(17, IDB_SMALLBAT, M_OBJECT);
	addElement(18, IDB_BIGBAT, M_OBJECT);
	addElement(19, IDB_REDBAT, M_OBJECT);
}

//�������ӽ�㣬��type���������������ͣ������������򷵻�false
bool Manager::addElement(int id, UINT resourceId, int type){
	node *current = head;
	while (current->next)
	{
		current = current->next;
	}
	if (type == M_ENEMY)
		current->next = new node(id, resourceId, M_ENEMY, hInstance);
	else if (type == M_PLAYER)
		current->next = new node(id, resourceId, M_PLAYER, hInstance);
	else if (type == M_OBJECT)
		current->next = new node(id, resourceId, M_OBJECT, hInstance);
	else
		return false;
	length++;
	return true;
}

//���ݽ���id�õ����ĵ�ַ
Object *Manager::Search(int id){
	node *current = head->next;
	while (current)
	{
		if (current->data->getId() == id)
		{
			return current->data;
		}
		current = current->next;
	}
	return nullptr;
}

//�������
void Manager::clear(){
	node *p;
	while (head->next){
		p = head->next;
		head->next = p->next;
		delete p;
	}
}

//��������Ƿ���ɱ������
bool Manager::calcDamage(Enemy *enemy)
{
	int playerHealth = getPlayer()->getHealth();
	int playerAttack = getPlayer()->getAttack();
	int playerDefense = getPlayer()->getDefense();
	int enemyHealth = enemy->getHealth();
	int enemyAttack = enemy->getAttack();
	int enemyDefense = enemy->getDefense();
	//��������������ҹ����߻���ȣ������ﲻ������������£�����false
	if (enemyDefense >= playerAttack)
		return false;
	//�������������������������������������false����������������true
	while (playerHealth > 0)
	{
		//����ȹ�������󹥣�����ҹ������������������ﲻ����
		enemyHealth -= (playerAttack - enemyDefense);
		if (enemyHealth < 0)
			return true;
		playerHealth -= (enemyAttack - playerDefense);
	}
	return false;
}
/*
//����ս������
void Manager::Fight(HWND hwnd, int floor, int x, int y)
{
	if (calcDamage()){
		//DialogBox(hIns, (LPCTSTR)IDD_FIGHT, hwnd, (DLGPROC)FIGHT);
		//map[floor - 1][y][x] = 0;
	}
}*/

void Manager::DrawMap(HDC hdc, MapManager *mm){
	Search(BACKGROUND)->PaintFromZero(hdc);

	for (int x = 0; x < 11; x++){
		for (int y = 0; y < 11; y++){
			Object *p = Search(mm->Loacate(mm->getCurrentFloor())->map[x][y]);
			//x��֮ǰ�Ĵ�����ָ�����Ǿ�����У����Ǵ�ӡ����Ļ��ʱxָ�����Ǻ����꣬��������У����Դ�ӡʱҪ��x��y�Ե�
			if (p)
				p->Paint(hdc, y, x);
		}
	}
	getPlayer()->Paint(hdc);
}

void Manager::PrintInfo(HDC hdc){
	LPCWSTR buffer = nullptr;
	char b[20];
	TextOut(hdc, 650, 100, buffer, sprintf_s(b, "����ֵ:%d", 1));
	TextOut(hdc, 650, 120, buffer, sprintf_s(b, "������:%d", 1));
	TextOut(hdc, 650, 140, buffer, sprintf_s(b, "������:%d", 1));
	TextOut(hdc, 650, 160, buffer, sprintf_s(b, "��Ǯ:%d", 1));
	TextOut(hdc, 650, 180, buffer, sprintf_s(b, "Կ��:%d", 1));
}

#endif
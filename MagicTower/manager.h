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

//结点保存object类对象，object类中包含位图及对应的名字
struct node{
	//默认构造函数，创建头结点时需要用到
	node(node *p = nullptr){ next = p; }
	//因为这个链表不需要在中间插入，只会在最后增加，所以在构造函数中直接为next赋空值
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

//manager类作为链表管理结点
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

//链表增加结点，由type决定新增结点的类型，若都不符合则返回false
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

//根据结点的id得到结点的地址
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

//清空链表
void Manager::clear(){
	node *p;
	while (head->next){
		p = head->next;
		head->next = p->next;
		delete p;
	}
}

//计算玩家是否能杀死怪物
bool Manager::calcDamage(Enemy *enemy)
{
	int playerHealth = getPlayer()->getHealth();
	int playerAttack = getPlayer()->getAttack();
	int playerDefense = getPlayer()->getDefense();
	int enemyHealth = enemy->getHealth();
	int enemyAttack = enemy->getAttack();
	int enemyDefense = enemy->getDefense();
	//如果怪物防御比玩家攻击高或相等，即怪物不可能死的情况下，返回false
	if (enemyDefense >= playerAttack)
		return false;
	//计算怪物先死还是玩家先死，若玩家先死返回false，若怪物先死返回true
	while (playerHealth > 0)
	{
		//玩家先攻，怪物后攻，若玩家攻击后怪物死亡，则怪物不攻击
		enemyHealth -= (playerAttack - enemyDefense);
		if (enemyHealth < 0)
			return true;
		playerHealth -= (enemyAttack - playerDefense);
	}
	return false;
}
/*
//进入战斗界面
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
			//x在之前的代码里指代的是矩阵的行，但是打印在屏幕上时x指代的是横坐标，即矩阵的列，所以打印时要把x和y对调
			if (p)
				p->Paint(hdc, y, x);
		}
	}
	getPlayer()->Paint(hdc);
}

void Manager::PrintInfo(HDC hdc){
	LPCWSTR buffer = nullptr;
	char b[20];
	TextOut(hdc, 650, 100, buffer, sprintf_s(b, "生命值:%d", 1));
	TextOut(hdc, 650, 120, buffer, sprintf_s(b, "攻击力:%d", 1));
	TextOut(hdc, 650, 140, buffer, sprintf_s(b, "防御力:%d", 1));
	TextOut(hdc, 650, 160, buffer, sprintf_s(b, "金钱:%d", 1));
	TextOut(hdc, 650, 180, buffer, sprintf_s(b, "钥匙:%d", 1));
}

#endif
#ifndef MANAGER_H
#define MANAGER_H

#include <Windows.h>
#include "definitions.h"
#include "map.h"
#include "object.h"
#include "player.h"
#include "enemy.h"
#include "road.h"
#include "upstairs.h"
#include "downstairs.h"
#include "door.h"
#include "key.h"

//结点保存object类对象，object类中包含位图及对应的名字
struct node{
	//默认构造函数，创建头结点时需要用到
	node(node *p = nullptr){ next = p; }
	//因为这个链表不需要在中间插入，只会在最后增加，所以在构造函数中直接为next赋空值
	node(int id, UINT resourceId, int type, HINSTANCE hIns);
	Object *data;
	node *next;
};

node::node(int id, UINT resourceId, int type, HINSTANCE hIns){
	switch (type){
	case TYPE_ENEMY:
		data = new Enemy(id, resourceId, hIns);
		break;
	case TYPE_PLAYER:
		data = new Player(id, resourceId, hIns);
		break;
	case TYPE_OBJECT:
		data = new Object(id, resourceId, hIns);
		break;
	case TYPE_ROAD:
		data = new Road(id, resourceId, hIns);
		break;
	case TYPE_UPSTAIRS:
		data = new Upstairs(id, resourceId, hIns);
		break;
	case TYPE_DOWNSTAIRS:
		data = new Downstairs(id, resourceId, hIns);
		break;
	case TYPE_DOOR:
		data = new Door(id, resourceId, hIns);
		break;
	case TYPE_KEY:
		data = new Key(id, resourceId, hIns);
		break;
	}
	next = nullptr;
}

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
	addElement(-2, IDB_PLAYER, TYPE_PLAYER);
	addElement(-1, IDB_BACKGROUND, TYPE_OBJECT);
	addElement(0, NULL, TYPE_ROAD);
	addElement(1, IDB_WALL, TYPE_OBJECT);
	addElement(2, IDB_UPSTAIRS, TYPE_UPSTAIRS);
	addElement(3, IDB_DOWNSTAIRS, TYPE_DOWNSTAIRS);
	addElement(4, IDB_DOOR, TYPE_DOOR);
	addElement(5, IDB_KEY, TYPE_KEY);
	addElement(6, IDB_SHOP, TYPE_OBJECT);
	addElement(7, IDB_BLUEGEM, TYPE_OBJECT);
	addElement(8, IDB_REDGEM, TYPE_OBJECT);
	addElement(9, IDB_SMALLMED, TYPE_OBJECT);
	addElement(10, IDB_BIGMED, TYPE_OBJECT);
	addElement(11, IDB_GREENSLIME, TYPE_ENEMY);
	addElement(12, IDB_REDSLIME, TYPE_ENEMY);
	addElement(13, IDB_BLACKSLIME, TYPE_ENEMY);
	addElement(14, IDB_SKELETON, TYPE_ENEMY);
	addElement(15, IDB_SKELETONSOLDIER, TYPE_ENEMY);
	addElement(16, IDB_SKELETONCAPTAIN, TYPE_ENEMY);
	addElement(17, IDB_SMALLBAT, TYPE_ENEMY);
	addElement(18, IDB_BIGBAT, TYPE_ENEMY);
	addElement(19, IDB_REDBAT, TYPE_ENEMY);
}

//链表增加结点，由type决定新增结点的类型，若都不符合则返回false
bool Manager::addElement(int id, UINT resourceId, int type){
	//取得链表最后一个结点的地址
	node *current = head;
	while (current->next){
		current = current->next;
	}
	//由type决定新结点中储存对象的类型
	current->next = new node(id, resourceId, type, hInstance);
	//若添加失败，则返回false
	if (!current->next) return false;
	//成功则返回true
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
			Object *p = Search(mm->Locate(mm->getCurrentFloor())->map[x][y]);
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
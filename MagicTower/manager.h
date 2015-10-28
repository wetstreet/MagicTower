#ifndef MANAGER_H
#define MANAGER_H

#include <Windows.h>
#include <sstream>
#include "definitions.h"
#include "map.h"
#include "general.h"

#include "object.h"
#include "player.h"
#include "enemy.h"

#include "road.h"
#include "upstairs.h"
#include "downstairs.h"
#include "door.h"
#include "key.h"
#include "shop.h"
#include "bluegem.h"
#include "redgem.h"
#include "smallmed.h"
#include "bigmed.h"
using namespace std;

//结点保存object类对象，object类中包含位图及对应的名字
struct node{
	//默认构造函数，创建头结点时需要用到
	node(node *p = nullptr){ next = p; }
	//因为这个链表不需要在中间插入，只会在最后增加，所以在构造函数中直接为next赋空值
	node(int id, UINT resourceId, int type, HINSTANCE hIns, int health, int attack, int defense, int money);
	Object *data;
	node *next;
};

//由Manager::AddElement传来的参数初始化新节点中的data
node::node(int id, UINT resourceId, int type, HINSTANCE hIns, int health, int attack, int defense, int money){
	switch (type){
	case TYPE_ENEMY:
		data = new Enemy(id, resourceId, hIns, health, attack, defense, money);
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
	case TYPE_SHOP:
		data = new Shop(id, resourceId, hIns);
		break;
	case TYPE_BLUEGEM:
		data = new BlueGem(id, resourceId, hIns);
		break;
	case TYPE_REDGEM:
		data = new RedGem(id, resourceId, hIns);
		break;
	case TYPE_SMALLMED:
		data = new SmallMed(id, resourceId, hIns);
		break;
	case TYPE_BIGMED:
		data = new BigMed(id, resourceId, hIns);
		break;
	}
	next = nullptr;
}

//manager类作为链表管理结点
class Manager{
public:
	Manager(HINSTANCE hIns, HWND hWnd) :hInstance(hIns), hMainWindow(hWnd), length(0){ head = new node; Initialize(); }
	void Initialize();
	~Manager(){ clear(); }
	void clear();
	Object *Search(int);
	int	getLength(){ return length; }
	Player *getPlayer(){ return (Player*)Search(ID_PLAYER); }
	bool AddElement(int id, UINT resourceId, int type, int health = 0, int attack = 0, int defense = 0, int money = 0);
	void DrawMap(HDC hdc, MapManager *mm);
	void PrintPlayerInfo(HDC hdc);
	void OnKeyDown(WPARAM wparam, MapManager *map, WindowManager *wm);
private:
	int length;
	node *head;
	HINSTANCE hInstance;
	HWND hMainWindow;
};

//在manager类初始化时注册各个对象
void Manager::Initialize(){
	AddElement(-2, IDB_PLAYER, TYPE_PLAYER);
	AddElement(-1, IDB_BACKGROUND, TYPE_OBJECT);
	AddElement(0, NULL, TYPE_ROAD);
	AddElement(1, IDB_WALL, TYPE_OBJECT);
	AddElement(2, IDB_UPSTAIRS, TYPE_UPSTAIRS);
	AddElement(3, IDB_DOWNSTAIRS, TYPE_DOWNSTAIRS);
	AddElement(4, IDB_DOOR, TYPE_DOOR);
	AddElement(5, IDB_KEY, TYPE_KEY);
	AddElement(6, IDB_SHOP, TYPE_SHOP);
	AddElement(7, IDB_BLUEGEM, TYPE_BLUEGEM);
	AddElement(8, IDB_REDGEM, TYPE_REDGEM);
	AddElement(9, IDB_SMALLMED, TYPE_SMALLMED);
	AddElement(10, IDB_BIGMED, TYPE_BIGMED);
	AddElement(11, IDB_GREENSLIME, TYPE_ENEMY, 50, 20, 1, 1);
	AddElement(12, IDB_REDSLIME, TYPE_ENEMY, 70, 15, 2, 2);
	AddElement(13, IDB_BLACKSLIME, TYPE_ENEMY, 200, 35, 10, 5);
	AddElement(14, IDB_SKELETON, TYPE_ENEMY, 110, 25, 5, 5);
	AddElement(15, IDB_SKELETONSOLDIER, TYPE_ENEMY, 150, 40, 20, 8);
	AddElement(16, IDB_SKELETONCAPTAIN, TYPE_ENEMY, 400, 90, 50, 15);
	AddElement(17, IDB_SMALLBAT, TYPE_ENEMY, 100, 20, 5, 3);
	AddElement(18, IDB_BIGBAT, TYPE_ENEMY, 150, 60, 35, 10);
	AddElement(19, IDB_REDBAT, TYPE_ENEMY, 550, 160, 90, 25);
}

//在链表尾链表添加结点，由type决定新增结点的类型，若都不符合则返回false
bool Manager::AddElement(int id, UINT resourceId, int type, int health, int attack, int defense, int money){
	//取得链表最后一个结点的地址
	node *current = head;
	while (current->next){
		current = current->next;
	}
	//由type决定新结点中储存对象的类型
	current->next = new node(id, resourceId, type, hInstance, health, attack, defense, money);
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

void Manager::DrawMap(HDC hdc, MapManager *mm){
	Search(ID_BACKGROUND)->PaintFromZero(hdc);

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

void Manager::PrintPlayerInfo(HDC hdc){
	Player *p = getPlayer();
	wstring s;
	s = L"生命值：" + IntToWString(p->getHealth());
	TextOut(hdc, 650, 80, s.c_str(), s.length());
	s = L"攻击力：" + IntToWString(p->getAttack());
	TextOut(hdc, 650, 100, s.c_str(), s.length());
	s = L"防御力：" + IntToWString(p->getDefense());
	TextOut(hdc, 650, 120, s.c_str(), s.length());
	s = L"金钱：" + IntToWString(p->getMoney());
	TextOut(hdc, 650, 140, s.c_str(), s.length());
	s = L"钥匙：" + IntToWString(p->getKey());
	TextOut(hdc, 650, 160, s.c_str(), s.length());
}

void Manager::OnKeyDown(WPARAM wparam, MapManager *map, WindowManager *wm){
	Player *p = getPlayer();
	int x = p->getX();
	int y = p->getY();
	int currentFloor = map->getCurrentFloor();

	switch (wparam){
	case VK_UP:
		if (y > 0){
			Search(map->getNumber(currentFloor, x, y - 1))->MeetPlayer(currentFloor, x, y - 1, p, map, wm);
		}
		break;
	case VK_DOWN:
		if (y < 10){
			Search(map->getNumber(currentFloor, x, y + 1))->MeetPlayer(currentFloor, x, y + 1, p, map, wm);
		}
		break;
	case VK_LEFT:
		if (x > 0){
			Search(map->getNumber(currentFloor, x - 1, y))->MeetPlayer(currentFloor, x - 1, y, p, map, wm);
		}
		break;
	case VK_RIGHT:
		if (x < 10){
			Search(map->getNumber(currentFloor, x + 1, y))->MeetPlayer(currentFloor, x + 1, y, p, map, wm);
		}
		break;
	}
}

#endif
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

//��㱣��object�����object���а���λͼ����Ӧ������
struct node{
	//Ĭ�Ϲ��캯��������ͷ���ʱ��Ҫ�õ�
	node(node *p = nullptr){ next = p; }
	//��Ϊ���������Ҫ���м���룬ֻ����������ӣ������ڹ��캯����ֱ��Ϊnext����ֵ
	node(int id, UINT resourceId, int type, HINSTANCE hIns, int health, int attack, int defense, int money);
	Object *data;
	node *next;
};

//��Manager::AddElement�����Ĳ�����ʼ���½ڵ��е�data
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

//manager����Ϊ���������
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

//��manager���ʼ��ʱע���������
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

//������β������ӽ�㣬��type���������������ͣ������������򷵻�false
bool Manager::AddElement(int id, UINT resourceId, int type, int health, int attack, int defense, int money){
	//ȡ���������һ�����ĵ�ַ
	node *current = head;
	while (current->next){
		current = current->next;
	}
	//��type�����½���д�����������
	current->next = new node(id, resourceId, type, hInstance, health, attack, defense, money);
	//�����ʧ�ܣ��򷵻�false
	if (!current->next) return false;
	//�ɹ��򷵻�true
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

void Manager::DrawMap(HDC hdc, MapManager *mm){
	Search(ID_BACKGROUND)->PaintFromZero(hdc);

	for (int x = 0; x < 11; x++){
		for (int y = 0; y < 11; y++){
			Object *p = Search(mm->Locate(mm->getCurrentFloor())->map[x][y]);
			//x��֮ǰ�Ĵ�����ָ�����Ǿ�����У����Ǵ�ӡ����Ļ��ʱxָ�����Ǻ����꣬��������У����Դ�ӡʱҪ��x��y�Ե�
			if (p)
				p->Paint(hdc, y, x);
		}
	}
	getPlayer()->Paint(hdc);
}

void Manager::PrintPlayerInfo(HDC hdc){
	Player *p = getPlayer();
	wstring s;
	s = L"����ֵ��" + IntToWString(p->getHealth());
	TextOut(hdc, 650, 80, s.c_str(), s.length());
	s = L"��������" + IntToWString(p->getAttack());
	TextOut(hdc, 650, 100, s.c_str(), s.length());
	s = L"��������" + IntToWString(p->getDefense());
	TextOut(hdc, 650, 120, s.c_str(), s.length());
	s = L"��Ǯ��" + IntToWString(p->getMoney());
	TextOut(hdc, 650, 140, s.c_str(), s.length());
	s = L"Կ�ף�" + IntToWString(p->getKey());
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
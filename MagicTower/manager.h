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

//��㱣��object�����object���а���λͼ����Ӧ������
struct node{
	//Ĭ�Ϲ��캯��������ͷ���ʱ��Ҫ�õ�
	node(node *p = nullptr){ next = p; }
	//��Ϊ���������Ҫ���м���룬ֻ����������ӣ������ڹ��캯����ֱ��Ϊnext����ֵ
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

//�������ӽ�㣬��type���������������ͣ������������򷵻�false
bool Manager::addElement(int id, UINT resourceId, int type){
	//ȡ���������һ�����ĵ�ַ
	node *current = head;
	while (current->next){
		current = current->next;
	}
	//��type�����½���д�����������
	current->next = new node(id, resourceId, type, hInstance);
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
			Object *p = Search(mm->Locate(mm->getCurrentFloor())->map[x][y]);
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
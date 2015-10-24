#ifndef MAPMANAGER_H
#define MAPMANAGER_H

#include <windows.h>
#include <fstream>
#include <sstream>
using namespace std;

struct MapNode{
	MapNode(MapNode *link = nullptr) :next(link){}
	int map[11][11];
	MapNode *next;
};

class MapManager{
public:
	MapManager() :currentFloor(1), mapNumber(0){ head = new MapNode; LoadMap(); }
	int getMapNumber()const{ return mapNumber; }
	MapNode *Locate(int number);
	int getNumber(int floor, int x, int y);
	void setNumber(int floor, int x, int y, int number);
	int getCurrentFloor()const{ return currentFloor; }
	int setCurrentFloor(int i){ currentFloor = i; }
	//��¥����
	void GoUp(){ currentFloor++; }
	//��¥����
	void GoDown(){ currentFloor--; }
private:
	void LoadMap();
	int currentFloor;
	int mapNumber;
	MapNode *head;
};

int MapManager::getNumber(int floor, int x, int y){
	MapNode *p = Locate(floor);
	return p->map[y][x];
}

void MapManager::setNumber(int floor, int x, int y, int number){
	MapNode *p = Locate(floor);
	p->map[y][x] = number;
}

MapNode *MapManager::Locate(int number){
	MapNode *current = head;
	for (int i = 0; i < number; i++)
	{
		current = current->next;
		if (!current)
			return nullptr;
	}
	return current;
}

void MapManager::LoadMap()
{
	//�ļ���д
	ifstream fin;
	//��ʽת��
	stringstream stream;
	string path;
	string s;

	//��Ϊ��ͼ�Ĳ����Ǵ�1��ʼ���ģ�����z��1��ʼ
	//��int��ת���ַ���
	int z = 1;
	while (1)
	{
		stream << z;
		stream >> s;
		stream.clear();
		path = "map\\" + s + ".txt";
		//��ȡ��ͼ�ļ�
		fin.open(path);
		//��Ϊ�ļ�������������ѭ��
		if (!fin)
			break;

		MapNode *current = head;
		while (current->next)
		{
			current = current->next;
		}
		current->next = new MapNode;
		for (int x = 0; x < 11; x++)
		{
			for (int y = 0; y < 11; y++)
			{
				fin >> current->next->map[x][y];
			}
		}
		fin.close();
		mapNumber++;
		//��ʼ��һ��ѭ������ȡ��һ���ļ�
		z++;
	}
}
#endif
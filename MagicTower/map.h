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
	MapNode *Loacate(int number);
	int getCurrentFloor()const{ return currentFloor; }
private:
	void LoadMap();
	int currentFloor;
	int mapNumber;
	MapNode *head;
};

MapNode *MapManager::Loacate(int number){
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
	//文件读写
	ifstream fin;
	//格式转换
	stringstream stream;
	string path;
	string s;

	//因为地图的层数是从1开始数的，所以z从1开始
	//将int型转成字符串
	int z = 1;
	while (1)
	{
		stream << z;
		stream >> s;
		stream.clear();
		path = "map\\" + s + ".txt";
		//读取地图文件
		fin.open(path);
		//若为文件不存在则跳出循环
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
		//开始下一次循环，读取下一个文件
		z++;
	}
}
#endif
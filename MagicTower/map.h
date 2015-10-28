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
	~MapManager(){ Clear(); }
	void Clear();
	int getMapNumber()const{ return mapNumber; }
	MapNode *Locate(int number);
	int getNumber(int floor, int x, int y);
	void setNumber(int floor, int x, int y, int number);
	int getCurrentFloor()const{ return currentFloor; }
	int setCurrentFloor(int i){ currentFloor = i; }
	//向楼上走
	void GoUp(){ currentFloor++; }
	//向楼下走
	void GoDown(){ currentFloor--; }
private:
	void LoadMap();
	int currentFloor;
	int mapNumber;
	MapNode *head;
};

void MapManager::Clear(){
	MapNode *del;
	MapNode *current = head;
	while (current->next){
		del = current;
		current = current->next->next;
		delete del;
		mapNumber--;
	}
}

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
	//文件读写
	ifstream fin;
	//格式转换
	stringstream stream;
	string path;
	string fileName;

	//因为地图的层数是从1开始数的，所以z从1开始
	//将int型转成字符串
	int fileNumber = 1;
	while (true){
		stream << fileNumber;
		stream >> fileName;
		stream.clear();
		path = "map\\" + fileName + ".txt";
		//读取地图文件
		fin.open(path);
		//若为文件不存在则跳出循环
		if (!fin)
			break;

		MapNode *current = head;
		while (current->next){
			current = current->next;
		}
		current->next = new MapNode;
		for (int x = 0; x < 11; x++){
			for (int y = 0; y < 11; y++){
				fin >> current->next->map[x][y];
			}
		}
		fin.close();
		mapNumber++;
		//开始下一次循环，读取下一个文件
		fileNumber++;
	}
}
#endif
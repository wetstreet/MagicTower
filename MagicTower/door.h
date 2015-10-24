#ifndef DOOR_H
#define DOOR_H

#include "object.h"

class Door :public Object{
public:
	Door(int id, UINT resourceId, HINSTANCE hIns) :Object(id, resourceId, hIns){}
	void MeetPlayer(int floor, int x, int y, Object *p, MapManager *m);
};

void Door::MeetPlayer(int floor, int x, int y, Object *p, MapManager *m){
	int key = p->getKey();
	if (key > 0){
		p->setKey(--key);
		m->setNumber(floor, x, y, 0);
		p->setX(x);
		p->setY(y);
	}
}

#endif
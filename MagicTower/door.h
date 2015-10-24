#ifndef DOOR_H
#define DOOR_H

#include "object.h"
#include "window.h"

class Door :public Object{
public:
	Door(int id, UINT resourceId, HINSTANCE hIns) :Object(id, resourceId, hIns){}
	void MeetPlayer(int floor, int x, int y, Object *p, MapManager *mm, WindowManager *wm);
};

void Door::MeetPlayer(int floor, int x, int y, Object *p, MapManager *mm, WindowManager *wm){
	int key = p->getKey();
	if (key > 0){
		p->setKey(--key);
		mm->setNumber(floor, x, y, 0);
	}
}

#endif
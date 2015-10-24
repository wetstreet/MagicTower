#ifndef UPSTAIRS_H
#define UPSTAIRS_H

#include "object.h"
#include "map.h"

class Upstairs :public Object{
public:
	Upstairs(int id, UINT resourceId, HINSTANCE hIns) :Object(id, resourceId, hIns){}
	void MeetPlayer(int floor, int x, int y, Object *p, MapManager *m);
};

void Upstairs::MeetPlayer(int floor, int x, int y, Object *p, MapManager *m){
	p->setX(x);
	p->setY(y);
	m->GoUp();
}

#endif
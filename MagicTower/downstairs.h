#ifndef DOWNSTAIRS_H
#define DOWNSTAIRS_H

#include "object.h"
#include "map.h"

class Downstairs :public Object{
public:
	Downstairs(int id, UINT resourceId, HINSTANCE hIns) :Object(id, resourceId, hIns){}
	void MeetPlayer(int floor, int x, int y, Object *p, MapManager *m);
};

void Downstairs::MeetPlayer(int floor, int x, int y, Object *p, MapManager *m){
	p->setX(x);
	p->setY(y);
	m->GoDown();
}

#endif
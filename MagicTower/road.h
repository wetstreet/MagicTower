#ifndef ROAD_H
#define ROAD_H

#include "object.h"

class Road:public Object{
public:
	Road(int id, UINT resourceId, HINSTANCE hIns) :Object(id, resourceId, hIns){}
	void MeetPlayer(int floor, int x, int y, Object *p, MapManager *m);
};

void Road::MeetPlayer(int floor, int x, int y, Object *p, MapManager *m){
	p->setX(x);
	p->setY(y);
}

#endif
#ifndef KEY_H
#define KEY_H

#include "object.h"

class Key :public Object{
public:
	Key(int id, UINT resourceId, HINSTANCE hIns) :Object(id, resourceId, hIns){}
	void MeetPlayer(int floor, int x, int y, Object *p, MapManager *m);
};

void Key::MeetPlayer(int floor, int x, int y, Object *p, MapManager *m){
	int key = p->getKey();
	p->setKey(++key);
	m->setNumber(floor, x, y, 0);
}

#endif
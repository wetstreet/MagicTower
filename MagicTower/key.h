#ifndef KEY_H
#define KEY_H

#include "object.h"
#include "window.h"

class Key :public Object{
public:
	Key(int id, UINT resourceId, HINSTANCE hIns) :Object(id, resourceId, hIns){}
	void MeetPlayer(int floor, int x, int y, Object *p, MapManager *mm, WindowManager *wm);
};

void Key::MeetPlayer(int floor, int x, int y, Object *p, MapManager *mm, WindowManager *wm){
	int key = p->getKey();
	p->setKey(++key);
	mm->setNumber(floor, x, y, 0);
}

#endif
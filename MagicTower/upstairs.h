#ifndef UPSTAIRS_H
#define UPSTAIRS_H

#include "object.h"
#include "map.h"

class Upstairs :public Object{
public:
	Upstairs(int id, UINT resourceId, HINSTANCE hIns) :Object(id, resourceId, hIns){}
	void MeetPlayer(int floor, int x, int y, Object *p, MapManager *mm, WindowManager *wm);
};

void Upstairs::MeetPlayer(int floor, int x, int y, Object *p, MapManager *mm, WindowManager *wm){
	Player *player = (Player *)p;
	player->setX(x);
	player->setY(y);
	mm->GoUp();
}

#endif
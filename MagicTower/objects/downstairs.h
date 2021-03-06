#ifndef DOWNSTAIRS_H
#define DOWNSTAIRS_H

#include "object.h"
#include "player.h"
#include "map.h"

class Downstairs :public Object{
public:
	Downstairs(int id, UINT resourceId, HINSTANCE hIns) :Object(id, resourceId, hIns){}
	void MeetPlayer(int floor, int x, int y, Object *p, MapManager *mm, WindowManager *wm);
};

void Downstairs::MeetPlayer(int floor, int x, int y, Object *p, MapManager *mm, WindowManager *wm){
	Player *player = (Player *)p;
	player->setX(x);
	player->setY(y);
	mm->GoDown();
}

#endif
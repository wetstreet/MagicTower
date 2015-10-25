#ifndef ROAD_H
#define ROAD_H

#include "object.h"
#include "player.h"
#include "window.h"

class Road:public Object{
public:
	Road(int id, UINT resourceId, HINSTANCE hIns) :Object(id, resourceId, hIns){}
	void MeetPlayer(int floor, int x, int y, Object *p, MapManager *mm, WindowManager *wm);
};

void Road::MeetPlayer(int floor, int x, int y, Object *p, MapManager *mm, WindowManager *wm){
	Player *player = (Player *)p;
	player->setX(x);
	player->setY(y);
}

#endif
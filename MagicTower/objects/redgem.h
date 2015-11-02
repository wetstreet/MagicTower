#ifndef REDGEM_H
#define REDGEM_H

#include "object.h"
#include "player.h"
#include <Windows.h>

class RedGem :public Object{
public:
	RedGem(int id, UINT resourceId, HINSTANCE hIns) :Object(id, resourceId, hIns){}
	void MeetPlayer(int floor, int x, int y, Object *p, MapManager *mm, WindowManager *wm);
};

void RedGem::MeetPlayer(int floor, int x, int y, Object *p, MapManager *mm, WindowManager *wm){
	Player *player = (Player *)p;
	player->AddAttack(3);
	mm->setNumber(floor, x, y, 0);
}

#endif